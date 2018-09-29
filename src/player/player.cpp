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
#include <cassert>
#include <gamelib2/math/vector.hpp>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Player
// -----------------------------------------------------------------------------
Player::Player(const std::string &in_name)
  : Entity(in_name) {
}

// -----------------------------------------------------------------------------
// activate
// -----------------------------------------------------------------------------
void Player::activate() {
    assert(widget.get());

    // init state machine
    std::unique_ptr<gamelib2::State> state(new Stand(this));
    init(state);
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Player::update(float dt) {
    Entity::update(dt);

    do_physics(dt);

    if (widget.get()) {
        widget->setPosition(position.x, position.y);
    }
    widget->animate();

    current_state->update(dt);
    if (current_state->finished()) {
        current_state->changeToNextState();
    }
}

// -----------------------------------------------------------------------------
// on_change_state
// -----------------------------------------------------------------------------
void Player::on_change_state() {
}

// -----------------------------------------------------------------------------
// do_physics
// -----------------------------------------------------------------------------
void Player::do_physics(float dt) {
    // has the sprite been manually moved
    gamelib2::Vector3 widget_position(widget->position().x,
                                      widget->position().y);
    if (!widget_position.equals(position)) {
        position.x = widget->position().x;
        position.y = widget->position().y;
    }

    // normalises to units
    velocity.normalise();

    // normalizes for diagonals
    if (velocity.magnitude() > speed) {
        velocity *= speed;
    }

    // basic euler motion
    velocity += acceleration * dt;
    position += velocity * dt * speed;
    acceleration.reset();
}
} // namespace senseless_soccer
