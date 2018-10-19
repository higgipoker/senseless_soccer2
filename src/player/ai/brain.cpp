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
#include "brain.hpp"
#include "../player.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Brain
// -----------------------------------------------------------------------------
Brain::Brain(Player *p)
  : player(p)
  , locomotion(player) {
    locomotion.change(LocomotionState::Stand);
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Brain::update(float dt) {
    locomotion.update(dt);
}

// -----------------------------------------------------------------------------
// handleMessage
// -----------------------------------------------------------------------------
void Brain::message(const std::string &msg) {
    if (msg.compare("receive")) {
        locomotion.change(LocomotionState::Pursue, Player::ball->position);
    } else if (msg.compare("dribble")) {
        locomotion.change(LocomotionState::Stand);
    }
}
} // namespace senseless_soccer
