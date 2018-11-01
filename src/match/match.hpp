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
#include <gamelib2/game/entity.hpp>
#include <memory>
#include "../team/team.hpp"

namespace senseless_soccer {
namespace match {
class Match : public gamelib2::Entity {
 public:
  Match();
  void init(team::Team *t1, team::Team *t2);
  void update(float dt);
  team::Team *team1 = nullptr;
  team::Team *team2 = nullptr;

 private:
 public:
  friend class Play;
};
}  // namespace match
}  // namespace senseless_soccer
