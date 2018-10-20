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
#include "locomotionmanager.hpp"
#include "../player.hpp"

namespace senseless_soccer {
namespace locomotion {

// -----------------------------------------------------------------------------
// LocomotionManager
// -----------------------------------------------------------------------------
LocomotionManager::LocomotionManager(Player *player)
  : stand(player)
  , pursue(player)
  , seek(player) {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void LocomotionManager::update(float dt) {
    if (current_locomotion != nullptr) {
        current_locomotion->update(dt);
        if (current_locomotion->finished()) {
            current_locomotion->stop();
            current_locomotion = &stand;
        }
    }
}

// -----------------------------------------------------------------------------
// startStand
// -----------------------------------------------------------------------------
void LocomotionManager::startStand() {
    current_locomotion->stop();
    current_locomotion = &stand;
    current_locomotion->start();
}

// -----------------------------------------------------------------------------
// startPursue
// -----------------------------------------------------------------------------
void LocomotionManager::startPursue(Vector3 *target) {
    current_locomotion->stop();
    pursue.init(target);
    current_locomotion = &pursue;
    current_locomotion->start();
}

// -----------------------------------------------------------------------------
// startSeek
// -----------------------------------------------------------------------------
void LocomotionManager::startSeek(const Vector3 &target) {
    current_locomotion->stop();
    seek.init(target);
    current_locomotion = &seek;
    current_locomotion->start();
}
} // namespace locomotion
} // namespace senseless_soccer
