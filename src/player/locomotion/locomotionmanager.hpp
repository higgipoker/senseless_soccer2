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
#pragma once
#include "head.hpp"
#include "pursue.hpp"
#include "seek.hpp"
#include "slide.hpp"
#include "stand.hpp"

#include <map>

namespace senseless_soccer {
class Player;
namespace locomotion {
enum class LocomotionState { Stand, Pursue, Seek, Head, Slide };
class LocomotionManager {
public:
  LocomotionManager(Player &player);
  void update(float dt);

  void startStand();
  void startPursue(Entity *target);
  void startSeek(const Vector3 &target);
  void startHead(const Vector3 &direction);
  void startSlide();

  void cancel();

  // distnostic map
  static std::map<std::string, LocomotionState> loco_map;
  static std::map<LocomotionState, std::string> reverse_loco_map;
  Locomotion &currentLocomotion();

private:
  Stand stand;
  Pursue pursue;
  Seek seek;
  Slide slide;
  Head head;
  Locomotion *current_locomotion = &stand;
};
} // namespace locomotion
} // namespace senseless_soccer
