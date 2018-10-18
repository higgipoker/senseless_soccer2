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

// -----------------------------------------------------------------------------
// LocomotionManager
// -----------------------------------------------------------------------------
LocomotionManager::LocomotionManager(Player *player)
  : pursue(player) {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void LocomotionManager::update(float dt) {
    if (current_locomotion != nullptr) {
        current_locomotion->update(dt);
        if (current_locomotion->finished()) {
            current_locomotion->stop();
            current_locomotion = nullptr;
        }
    }
}

// -----------------------------------------------------------------------------
// change
// -----------------------------------------------------------------------------
void LocomotionManager::change(const LocomotionState state,
                               const Vector3 &static_target,
                               const Vector3 *dynamic_target) {
    switch (state) {
    case LocomotionState::Pursue:
        current_locomotion = &pursue;
        break;
    case LocomotionState::Seek:
        break;
    }
    current_locomotion->init(static_target, dynamic_target);
    current_locomotion->start();
}
} // namespace senseless_soccer
