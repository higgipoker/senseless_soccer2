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
#include "dribble.hpp"
#include "../../../pitch/pitch.hpp"
#include "../../player.hpp"
#include "../brain.hpp"

#include "gamelib2/math/vector.hpp"

using namespace gamelib2;
namespace senseless_soccer {
namespace ai {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Dribble::Dribble(Brain &b) : BrainState(b, "dribble") {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Dribble::start() {
  brain.locomotion.startHead(brain.player.facing.toVector());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Dribble::stop() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Dribble::finished() { return !brain.player.ball_under_control(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Dribble::update(float dt) {
  if (++ticks > 100) {
    ticks = 0;
    change_direction();
  }
  stay_in_pitch(dt);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Dribble::change_direction(int angle) {
  Vector3 new_direction = brain.player.brain.player.velocity
                              .rotate(rand() % 2 == 1 ? angle : -angle)
                              .roundAngle(45);
  brain.locomotion.startHead(new_direction);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Dribble::stay_in_pitch(float dt) {
  sf::FloatRect boundary = Player::pitch->dimensions.bounds;
  sf::Vector2f p(brain.player.position.z, brain.player.position.y);
  Vector3 next_position =
      brain.player.position + brain.player.velocity * brain.player.speed * dt;

  // if the player is outside the boundary (eg taking throw in) let him move
  // back in!

  if (boundary.contains(p)) {
    // keep inside boundary

    if (next_position.x < boundary.left) {
      brain.player.velocity.x = 0;
    }

    if (next_position.x > (boundary.left + boundary.width)) {
      brain.player.velocity.x = 0;
    }

    if (next_position.y < boundary.top) {
      brain.player.velocity.y = 0;
    }

    if (next_position.y > (boundary.top + boundary.height)) {
      brain.player.velocity.y = 0;
    }

  } else {
    // get back onto the pitch as soon as possible
    if (brain.player.position.x < boundary.left) {
      change_direction(90);
    }

    if (brain.player.position.x > (boundary.left + boundary.width)) {
      change_direction(90);
    }

    if (brain.player.position.y < boundary.top) {
      change_direction(90);
    }

    if (brain.player.position.y > (boundary.top + boundary.height)) {
      change_direction(90);
    }
  }
}

} // namespace ai
} // namespace senseless_soccer
