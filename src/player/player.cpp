/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#include "player.hpp"

#include "states/running.hpp"
#include "states/standing.hpp"

#include "../joysticker/aftertouch.hpp"
#include "../metrics/metrics.hpp"
#include "../team/team.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/physics/collisions.hpp>

#include <algorithm>
#include <cassert>

using namespace gamelib2;
namespace senseless_soccer {

std::map<gamelib2::Direction, std::string> Player::stand_animation_map;
std::map<gamelib2::Direction, std::string> Player::run_animation_map;
std::map<gamelib2::Direction, std::string> Player::slide_animation_map;

Ball *Player::ball = nullptr;
Pitch *Player::pitch = nullptr;

// tmp - these will be player attribs
static const float dribble_radius = 2.f;
static const float control_radius = 8.f;

// -----------------------------------------------------------------------------
// Player
// -----------------------------------------------------------------------------
Player::Player(std::string in_name)
    : Entity("player", std::move(in_name)),
      brain(*this),
      debug_short_pass(sf::Triangles, 3),
      stand_state(*this),
      run_state(*this),
      slide_state(*this),
      jump_state(*this) {
  feet.setRadius(dribble_radius);
  control_inner.setRadius(control_radius);
  control_outer.setRadius(control_radius * 1.2f);
}

// -----------------------------------------------------------------------------
// activate
// -----------------------------------------------------------------------------
void Player::activate() {
  // init state machine
  change_state(PlayerState::Stand);
  current_state->start();
  speed = 200;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Player::update(float dt) {
  Entity::update(dt);

  // cpu controlled locomotion
  if (!controller) {
    brain.update(dt);
  }

  // movement
  do_physics(dt);

  // direction tracking
  if (velocity.magnitude()) {
    facing.fromVector(velocity);
    if (facing != facing_old) {
      changed_direction = true;
    } else {
      changed_direction = false;
    }
  }

  // update widget (sprite)
  if (widget) {
    auto sprite = dynamic_cast<Sprite *>(widget.get());

    sprite->setPosition(position.x, position.y);
    sprite->animate();

    // sync shadow with sprite
    auto shadow = sprite->getShadow();
    if (shadow.get() != nullptr) {
      shadow->setFrame(sprite->getFrame());
      shadow->setPosition(sprite->position().x, sprite->position().y);
    }

    feet.setPosition(position.x, position.y);
    control_inner.setPosition(feet.getPosition());
    control_outer.setPosition(feet.getPosition());

    widget->shapes.clear();
    widget->shapes.emplace_back(&feet);
  }

  perspectivize(CAMERA_HEIGHT);

  if (!ball_under_control()) {
    shooting = false;
  }

  // state machine
  current_state->update(dt);
  if (current_state->finished()) {
    current_state->end();
    current_state->changeToNextState();
    current_state->start();
  }

  facing_old = facing;
  distance_from_ball = (ball->position - position).magnitude();

  if (!in_possession) {
    if (Collision::collides(control_inner, Player::ball->circle)) {
      on_got_possession();
    }
  } else {
    if (!Collision::collides(control_inner, Player::ball->circle)) {
      on_lost_possession();
    }
  }

  if (in_possession) {
    calc_short_pass_recipients();
  }
}

// -----------------------------------------------------------------------------
// do_physics
// -----------------------------------------------------------------------------
void Player::do_physics(float dt) {
  // normalizes for diagonals
  if (Floats::greater_than(velocity.magnitude(), 0)) {
    velocity = velocity.normalise();
    velocity *= speed;
  }

  // basic euler motion
  velocity += acceleration * dt;
  position += velocity * dt;

  if (Floats::less_than(position.z, 0)) {
    position.z = 0;
  }
  acceleration.reset();
}

// -----------------------------------------------------------------------------
// OnControllerEvent
// -----------------------------------------------------------------------------
void Player::onControllerEvent(ControllerEvent event) {
  current_state->handle_input(event);
}

// -----------------------------------------------------------------------------
// onMoved
// -----------------------------------------------------------------------------
void Player::onDragged(const gamelib2::Vector3 &new_position) {
  Entity::onDragged(new_position);
}

// -----------------------------------------------------------------------------
// do_dribble
// -----------------------------------------------------------------------------
void Player::do_dribble() {
  // TODO height
  if (ball->position.z > 30) return;

  // calc force needed for kick
  float force_needed = speed * 200.0f;
  Vector3 kick = facing_old.toVector().normalise();

  if (Floats::greater_than(kick.magnitude(), 0)) {
    kick = kick.normalise();
    kick *= force_needed;
  }

  // apply the kick force to ball
  ball->kick(kick);
}

// -----------------------------------------------------------------------------
// do_close_control
// -----------------------------------------------------------------------------
void Player::do_close_control() {
  // player position + control range
  Vector3 f(feet.getPosition().x, feet.getPosition().y);
  Vector3 ball_pos = f + (facing.toVector() * 5);

  // reset ball
  ball->velocity.reset();

  // set new position
  ball->position = ball_pos;
}

// -----------------------------------------------------------------------------
// change_state
// -----------------------------------------------------------------------------
void Player::change_state(const PlayerState &state) {
  switch (state) {
    case PlayerState::Stand:
      current_state = &stand_state;
      break;
    case PlayerState::Run:
      current_state = &run_state;
      break;
    case PlayerState::Slide:
      current_state = &slide_state;
      break;
    case PlayerState::Jump:
      current_state = &jump_state;
      break;
  }
}

// -----------------------------------------------------------------------------
// kick
// -----------------------------------------------------------------------------
void Player::kick(const Vector3 &direction, unsigned int power) {
  // clamp the power
  power = std::max(min_pass_power, std::min(power, max_pass_power));

  // always kick in direction player is facing
  Vector3 force = direction;
  // force.z = force.magnitude() * 0.001f;

  // normalise for diagonals
  if (Floats::greater_than(force.magnitude(), 0)) {
    force = force.normalise();
    force *= power * 1000;
  }

  //  apply to ball
  ball->kick(force);

  //  start aftertouch and apply initial extra force to ball depending on dpad
  if (controller) {
    controller->startAftertouch(ball, force.normalise(), force.magnitude());
  }

  // temp suspend control and dribble
  shooting = true;
}

// -----------------------------------------------------------------------------
// short_pass
// -----------------------------------------------------------------------------
void Player::short_pass() {
  Player *receiver = calc_short_pass_receiver();

  if (receiver) {
    int distance =
        static_cast<int>((receiver->position - position).magnitude());
    Vector3 direction = receiver->position - position;
    Vector3 force = direction * distance * 1.4f;
    Player::ball->kick(force);
    receiver->brain.message("receive");
  } else {
    kick(facing.toVector(), 1);
  }

  shooting = true;
}

// -----------------------------------------------------------------------------
// shoot
// -----------------------------------------------------------------------------
void Player::shoot() {
  // for now just aim at center of goal
  Vector3 to_goal =
      Vector3(
          my_team->attacking_goal.left + my_team->attacking_goal.width / 2,
          my_team->attacking_goal.top + my_team->attacking_goal.height / 2) -
      position;
  kick(to_goal.normalise(), 60);
}

// -----------------------------------------------------------------------------
// slide
// -----------------------------------------------------------------------------
void Player::slide() { sliding = true; }

// -----------------------------------------------------------------------------
// jump
// -----------------------------------------------------------------------------
void Player::jump() { jumping = true; }

// -----------------------------------------------------------------------------
// ball_under_control
// -----------------------------------------------------------------------------
bool Player::ball_under_control() {
  return Collision::collides(control_inner, ball->circle);
}

// -----------------------------------------------------------------------------
// attachInput
// -----------------------------------------------------------------------------
void Player::attachInput(SensiController *c) {
  controller = c;
  controller->setListener(this);
  velocity.reset();
  current_state->on_controller_handover();
}

// -----------------------------------------------------------------------------
// detatchInput
// -----------------------------------------------------------------------------
void Player::detatchInput() {
  velocity.reset();
  controller = nullptr;
}

//--------------------------------------------------
//       [PLAYER]
//
//          p1
//          /\
//         /  \
//        /    \
//       /      \
//     p2--------p3
//
//  calc_short_pass_recipients
//  --------------------------------------------------
void Player::calc_short_pass_recipients() {
  // current position plus projected away from feet slightly
  Vector3 t1 = position + facing.toVector() * 10;

  // rotate x degrees and project out
  Vector3 temp1 = facing.toVector();
  Vector3 t2 = position + (temp1.rotate(40, 0, 0)).normalise() * 450;

  // rotate minus x degrees and project out
  Vector3 temp2 = facing.toVector();
  Vector3 t3 = position + (temp2.rotate(-40, 0, 0)).normalise() * 450;

  // save 3 points to triangle
  short_pass_triangle.p1 = Vector3(t1.x, t1.y);
  short_pass_triangle.p2 = Vector3(t2.x, t2.y);
  short_pass_triangle.p3 = Vector3(t3.x, t3.y);

  // diagnostics
  debug_short_pass[0].position = sf::Vector2f(t1.x, t1.y);
  debug_short_pass[1].position = sf::Vector2f(t2.x, t2.y);
  debug_short_pass[2].position = sf::Vector2f(t3.x, t3.y);
  debug_short_pass[0].color = sf::Color(0, 255, 0, 100);
  debug_short_pass[1].color = sf::Color(0, 255, 0, 100);
  debug_short_pass[2].color = sf::Color(0, 255, 0, 100);
  widget->primitives.emplace_back(debug_short_pass);
}

// -----------------------------------------------------------------------------
// on_got_possession
// -----------------------------------------------------------------------------
void Player::on_got_possession() {
  if (my_team) {
    in_possession = my_team->requestPossession(this);
  }
}

// -----------------------------------------------------------------------------
// on_lost_possession
// -----------------------------------------------------------------------------
void Player::on_lost_possession() {
  in_possession = false;
  my_team->lostPossession(this);
}

// -----------------------------------------------------------------------------
// calc_short_pass_receiver
// -----------------------------------------------------------------------------
Player *Player::calc_short_pass_receiver() {
  Player *p = nullptr;

  // get a list of players in my short pass range
  std::vector<Player *> candidates;
  for (auto &player : my_team->players) {
    // is in short pass range
    if (Collision::collides(player->position, short_pass_triangle)) {
      candidates.emplace_back(player);
    }
  }

  // tmp pick a random one
  if (!candidates.empty()) {
    p = candidates[0];
  }

  return p;
}

// -----------------------------------------------------------------------------
// setTeam
// -----------------------------------------------------------------------------
void Player::setTeam(team::Team *t) { my_team = t; }

// -----------------------------------------------------------------------------
// face_ball
// -----------------------------------------------------------------------------
void Player::face_ball() {
  if (widget) {
    if (Player::ball) {
      gamelib2::Vector3 to_ball = Player::ball->position - position;
      gamelib2::Compass c(to_ball.normalise());
      widget->startAnimation(Player::stand_animation_map[c.direction]);
      facing.fromVector(to_ball.normalise());
    } else {
      widget->startAnimation(
          Player::stand_animation_map[gamelib2::Direction::SOUTH]);
      facing = gamelib2::Direction::SOUTH;
    }
  }
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void Player::perspectivize(float camera_height) {
  // size depending on distance from camera
  float dimensions = 48;  // need to standardize heights /	pngs
  float dist_from_camera = camera_height - position.z;
  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / dimensions;

  auto sprite = dynamic_cast<Sprite *>(widget.get());

  float sprite_ratio = dimensions / sprite->image_width;
  sprite_scale_factor *= sprite_ratio;
  sprite->scale(sprite_scale_factor, sprite_scale_factor);

  // y offset due to height
  float z_cm = position.z * CM_PER_PIXEL;

  if (Floats::greater_than(z_cm, 0)) {
    // tmp hard code offset = 0.133px per cm
    float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
    sprite->move(0, -y_offset);
  }

  // update the shadow
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Player::triggerState(const PlayerState state) {
  current_state->end();
  change_state(state);
  current_state->start();
}

// -----------------------------------------------------------------------------
// init_animation_map
// -----------------------------------------------------------------------------
void Player::init() {
  // standing animations
  stand_animation_map.insert(
      std::make_pair(Direction::SOUTH_EAST, "stand_southeast"));
  stand_animation_map.insert(std::make_pair(Direction::SOUTH, "stand_south"));
  stand_animation_map.insert(
      std::make_pair(Direction::SOUTH_WEST, "stand_southwest"));
  stand_animation_map.insert(std::make_pair(Direction::WEST, "stand_west"));
  stand_animation_map.insert(
      std::make_pair(Direction::NORTH_WEST, "stand_northwest"));
  stand_animation_map.insert(std::make_pair(Direction::NORTH, "stand_north"));
  stand_animation_map.insert(
      std::make_pair(Direction::NORTH_EAST, "stand_northeast"));
  stand_animation_map.insert(std::make_pair(Direction::EAST, "stand_east"));

  // running animations
  run_animation_map.insert(
      std::make_pair(Direction::SOUTH_EAST, "run_southeast"));
  run_animation_map.insert(std::make_pair(Direction::SOUTH, "run_south"));
  run_animation_map.insert(
      std::make_pair(Direction::SOUTH_WEST, "run_southwest"));
  run_animation_map.insert(std::make_pair(Direction::WEST, "run_west"));
  run_animation_map.insert(
      std::make_pair(Direction::NORTH_WEST, "run_northwest"));
  run_animation_map.insert(std::make_pair(Direction::NORTH, "run_north"));
  run_animation_map.insert(
      std::make_pair(Direction::NORTH_EAST, "run_northeast"));
  run_animation_map.insert(std::make_pair(Direction::EAST, "run_east"));

  // sliding animations
  slide_animation_map.insert(
      std::make_pair(Direction::SOUTH_EAST, "slide_southeast"));
  slide_animation_map.insert(std::make_pair(Direction::SOUTH, "slide_south"));
  slide_animation_map.insert(
      std::make_pair(Direction::SOUTH_WEST, "slide_southwest"));
  slide_animation_map.insert(std::make_pair(Direction::WEST, "slide_west"));
  slide_animation_map.insert(
      std::make_pair(Direction::NORTH_WEST, "slide_northwest"));
  slide_animation_map.insert(std::make_pair(Direction::NORTH, "slide_north"));
  slide_animation_map.insert(
      std::make_pair(Direction::NORTH_EAST, "slide_northeast"));
  slide_animation_map.insert(std::make_pair(Direction::EAST, "slide_east"));
}

// -----------------------------------------------------------------------------
// stateName
// -----------------------------------------------------------------------------
std::string Player::stateName() { return current_state->name; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Player::setRole(std::shared_ptr<team::Position> r) { role = std::move(r); }
}  // namespace senseless_soccer
