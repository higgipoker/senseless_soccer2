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
#include "states/run.hpp"
#include "states/stand.hpp"
#include "../joysticker/aftertouch.hpp"
#include "../metrics/metrics.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/physics/collisions.hpp>

#include <cassert>
#include <algorithm>

using namespace gamelib2;
namespace senseless_soccer {

std::map<gamelib2::Direction, std::string> Player::stand_animation_map;
std::map<gamelib2::Direction, std::string> Player::run_animation_map;

Ball *Player::ball = nullptr;

// tmp - these will be player attribs
static const float dribble_radius = 2.f;
static const float control_radius = 8.f;

// -----------------------------------------------------------------------------
// Player
// -----------------------------------------------------------------------------
Player::Player(std::string in_name)
  : Entity(std::move(in_name))
  , stand_state(std::make_unique<Stand>(*this))
  , run_state(std::make_unique<Run>(*this)) {
    feet.setRadius(dribble_radius);
    control_inner.setRadius(control_radius);
    control_outer.setRadius(control_radius * 1.2f);
    current_state = stand_state.get();
}

// -----------------------------------------------------------------------------
// activate
// -----------------------------------------------------------------------------
void Player::activate() {
    // init state machine
    change_state(PlayerState::Stand);
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Player::update(float dt) {
    Entity::update(dt);

    // movement
    do_physics(dt);

    // direction tracking
    facing.fromVector(velocity);
    if (facing != facing_old) {
        changed_direction = true;
    } else {
        changed_direction = false;
    }

    // update widget (sprite)
    if (widget) {

        auto sprite = dynamic_cast<Sprite *>(widget.get());

        sprite->setPosition(position.x, position.y);
        sprite->animate();

        // sync shadow with sprite
        Sprite *shadow = sprite->getShadow();
        if (shadow) {
            shadow->setFrame(sprite->getFrame());
            shadow->setPosition(sprite->position().x, sprite->position().y);
        }

        feet.setPosition(sprite->position().x,
                         sprite->position().y + (sprite->image_height / 2) - 4);
        control_inner.setPosition(feet.getOrigin());
        control_outer.setPosition(feet.getOrigin());
    }

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
}

// -----------------------------------------------------------------------------
// do_physics
// -----------------------------------------------------------------------------
void Player::do_physics(float dt) {

    // normalizes for diagonals
    velocity = velocity.normalise();
    if (velocity.magnitude() > speed) {
        velocity *= speed;
    }

    // basic euler motion
    velocity += acceleration * dt;
    position += velocity * dt * speed;
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
    if (ball->position.z > 30)
        return;

    // calc force needed for kick
    float force_needed = speed * 200.0f;
    Vector3 kick = facing_old.toVector() * force_needed;

    // normalize for diagonals
    if (kick.magnitude() > force_needed) {
        kick /= kick.magnitude();
        kick *= force_needed;
    }

    // apply the kick force to ball
    ball->kick(kick);

    std::cout << "dribble" << std::endl;
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
        current_state = stand_state.get();
        break;

    case PlayerState::Run:
        current_state = run_state.get();
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
    Vector3 force = direction * power;

    //  apply to ball
    ball->kick(force * 1000);

    //  start aftertouch and apply initial extra force to ball depending on dpad
    controller->startAftertouch(ball, force.normalise(), force.magnitude());

    // temp suspend control and dribble
    shooting = true;
}

// -----------------------------------------------------------------------------
// short_pass
// -----------------------------------------------------------------------------
void Player::short_pass(const Player *receiver) {
    int distance =
      static_cast<int>((receiver->position - position).magnitude());

    std::cout << distance << std::endl;
}

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
    current_state->on_controller_handover();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Player::detatchInput() {
    velocity.reset();
    controller = nullptr;
}

//  --------------------------------------------------
//       [PLAYER]
//
//          p1
//          /\
//         /  \
//        /    \
//       /      \
//     p2--------p3
//
//  calc_pass_recipients
//  --------------------------------------------------
void Player::calc_short_pass_recipients() {

    // current position plus projected away from feet slightly
    Vector3 tmp = position;
    tmp = tmp + facing.toVector() * 20;

    // rotate 35 degrees and project out
    Vector3 temp1 = facing.toVector();
    Vector3 t1 = position + (temp1.rotate(35, 0, 0)).normalise() * 450;

    // rotate minus 35 degrees and project out
    Vector3 temp2 = facing.toVector();
    Vector3 t2 = position + (temp2.rotate(-35, 0, 0)).normalise() * 450;

    // save 3 points to triangle
    short_pass_triangle.p1 = Vector3(tmp.x, tmp.y);
    short_pass_triangle.p2 = Vector3(t1.x, t1.y);
    short_pass_triangle.p3 = Vector3(t2.x, t2.y);
}

// -----------------------------------------------------------------------------
// on_got_possession
// -----------------------------------------------------------------------------
void Player::on_got_possession() {
    in_possession = true;
}

// -----------------------------------------------------------------------------
// on_lost_possession
// -----------------------------------------------------------------------------
void Player::on_lost_possession() {
    in_possession = true;
}

// -----------------------------------------------------------------------------
// init_animation_map
// -----------------------------------------------------------------------------
void Player::Init() {

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
}
} // namespace senseless_soccer
