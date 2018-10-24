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

std::map<std::string, LocomotionState> LocomotionManager::loco_map = {
    std::make_pair("stand", LocomotionState::Stand),
    std::make_pair("pursue", LocomotionState::Pursue),
    std::make_pair("seek", LocomotionState::Seek),
    std::make_pair("slide", LocomotionState::Slide),
};

std::map<LocomotionState, std::string> LocomotionManager::reverse_loco_map = {
    std::make_pair(LocomotionState::Stand, "stand"),
    std::make_pair(LocomotionState::Pursue, "pursue"),
    std::make_pair(LocomotionState::Seek, "seek"),
    std::make_pair(LocomotionState::Slide, "slide"),
};

// -----------------------------------------------------------------------------
// LocomotionManager
// -----------------------------------------------------------------------------
LocomotionManager::LocomotionManager(Player &player)
    : stand(player), pursue(player), seek(player), slide(player) {}

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
void LocomotionManager::startPursue(Entity *target) {
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

// -----------------------------------------------------------------------------
// startSlide
// -----------------------------------------------------------------------------
void LocomotionManager::startSlide() {
  current_locomotion->stop();
  current_locomotion = &slide;
  current_locomotion->start();
}

// -----------------------------------------------------------------------------
// currentLocomotion
// -----------------------------------------------------------------------------
Locomotion &LocomotionManager::currentLocomotion() {
  return *current_locomotion;
}

// -----------------------------------------------------------------------------
// cancel
// -----------------------------------------------------------------------------
void LocomotionManager::cancel() { currentLocomotion().stop(); }
} // namespace locomotion
} // namespace senseless_soccer
