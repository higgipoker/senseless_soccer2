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
#include <cassert>
#include <gamelib2/math/vector.hpp>
#include <gamelib2/physics/collisions.hpp>

using namespace gamelib2;
namespace senseless_soccer {

std::map<gamelib2::Direction, std::string> Player::stand_animation_map;
std::map<gamelib2::Direction, std::string> Player::run_animation_map;

Ball *Player::ball = nullptr;

// tmp - these will be player attribs
static const float dribble_radius = 4.f;
static const float control_radius = 8.f;

// -----------------------------------------------------------------------------
// Player
// -----------------------------------------------------------------------------
Player::Player(std::string in_name)
  : Entity(std::move(in_name))
  , stand_state(new Stand(*this))
  , run_state(new Run(*this)) {
    feet.setRadius(dribble_radius);
    control.setRadius(control_radius);
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

    Aftertouch::update();

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

        Sprite *sprite = static_cast<Sprite *>(widget);

        sprite->setPosition(position.x, position.y);
        sprite->animate();

        // sync shadow with sprite
        Sprite *shadow = sprite->getShadow();
        if (shadow) {
            shadow->setFrame(sprite->getFrame());
            shadow->setPosition(sprite->position().x + 3,
                                sprite->position().y + 7);
        }

        feet.setPosition(sprite->position().x,
                         sprite->position().y + (sprite->image_height / 2) - 4);
        control = feet;
        control.setRadius(control_radius);
    }
    // state machine
    current_state->update(dt);
    if (current_state->finished()) {
        current_state->end();
        current_state->changeToNextState();
        current_state->start();
    }

    facing_old = facing;
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
void Player::onMoved(const gamelib2::Vector3 &new_position, float dx,
                     float dy) {
    Entity::onMoved(new_position);
    auto w = widget;
    w->setPosition(position.x, position.y);
    w->animate();
}

// -----------------------------------------------------------------------------
// do_dribble
// -----------------------------------------------------------------------------
void Player::do_dribble() {
    // TODO height
    if (ball->position.z > 30)
        return;

    // calc force needed for kick
    float force_needed = speed * 120.0f;
    Vector3 kick = facing_old.toVector() * force_needed;

    // normalize for diagonals
    if (kick.magnitude() > force_needed) {
        kick /= kick.magnitude();
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
void Player::kick(Vector3 force) {
    //  apply to ball
    ball->kick(force);

    //  start aftertouch!
    Aftertouch::startAftertouch(ball, controller, force.normalise());
}

// -----------------------------------------------------------------------------
// ball_under_control
// -----------------------------------------------------------------------------
bool Player::ball_under_control() {
    return Collision::collides(control, ball->circle);
}

// -----------------------------------------------------------------------------
// attachInput
// -----------------------------------------------------------------------------
void Player::attachInput(Controller *c) {
    controller = c;
    controller->setListener(this);
}

// -----------------------------------------------------------------------------
// init_animation_map
// -----------------------------------------------------------------------------
void Player::Init() {

    // should only be done once
    assert(stand_animation_map.empty());
    assert(run_animation_map.empty());

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
