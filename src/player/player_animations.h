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
#include <vector>
namespace senseless_soccer {
namespace player_animations {
const float anim_speed = 0.01f * 10.0f;

// -----------------------------------------------------------------------------
// standing animations
// -----------------------------------------------------------------------------
static std::vector<int> stand_east() { return std::vector<int>{1}; }
static std::vector<int> stand_southeast() { return std::vector<int>{4}; }
static std::vector<int> stand_south() { return std::vector<int>{7}; }
static std::vector<int> stand_southwest() { return std::vector<int>{10}; }
static std::vector<int> stand_west() { return std::vector<int>{13}; }
static std::vector<int> stand_northwest() { return std::vector<int>{16}; }
static std::vector<int> stand_north() { return std::vector<int>{19}; }
static std::vector<int> stand_northeast() { return std::vector<int>{22}; }

// -----------------------------------------------------------------------------
// running animations
// -----------------------------------------------------------------------------
static std::vector<int> run_east() { return std::vector<int>{0, 1}; }
static std::vector<int> run_southeast() { return std::vector<int>{3, 5}; }
static std::vector<int> run_south() { return std::vector<int>{6, 8}; }
static std::vector<int> run_southwest() { return std::vector<int>{9, 11}; }
static std::vector<int> run_west() { return std::vector<int>{12, 13}; }
static std::vector<int> run_northwest() { return std::vector<int>{15, 17}; }
static std::vector<int> run_north() { return std::vector<int>{18, 20}; }
static std::vector<int> run_northeast() { return std::vector<int>{21, 23}; }

// -----------------------------------------------------------------------------
// sliding animations
// -----------------------------------------------------------------------------
static std::vector<int> slide_east() {
  std::vector<int> v;
  v.push_back(24);
  v.push_back(25);
  for (int i = 0; i < 2; ++i) v.push_back(26);
  return v;
}
static std::vector<int> slide_southeast() {
  std::vector<int> v{27, 28};
  for (int i = 0; i < 2; ++i) v.push_back(29);
  return v;
}
static std::vector<int> slide_south() {
  std::vector<int> v{30, 31};
  for (int i = 0; i < 2; ++i) v.push_back(32);
  return v;
}
static std::vector<int> slide_southwest() {
  std::vector<int> v{33, 34};
  for (int i = 0; i < 2; ++i) v.push_back(35);
  return v;
}
static std::vector<int> slide_west() {
  std::vector<int> v{36, 37};
  for (int i = 0; i < 2; ++i) v.push_back(38);
  return v;
}
static std::vector<int> slide_northwest() {
  std::vector<int> v{39, 40};
  for (int i = 0; i < 2; ++i) v.push_back(41);
  return v;
}

static std::vector<int> slide_north() {
  std::vector<int> v{42, 43};
  for (int i = 0; i < 2; ++i) v.push_back(44);
  return v;
}
static std::vector<int> slide_northeast() {
  std::vector<int> v{45, 46};
  for (int i = 0; i < 2; ++i) v.push_back(47);
  return v;
}

static void fill_animations(gamelib2::Entity* e) {
  e->addAnimation("stand_east", anim_speed, true, stand_east());
  e->addAnimation("stand_southeast", anim_speed, true, stand_southeast());
  e->addAnimation("stand_south", anim_speed, true, stand_south());
  e->addAnimation("stand_southwest", anim_speed, true, stand_southwest());
  e->addAnimation("stand_west", anim_speed, true, stand_west());
  e->addAnimation("stand_northwest", anim_speed, true, stand_northwest());
  e->addAnimation("stand_north", anim_speed, true, stand_north());
  e->addAnimation("stand_northeast", anim_speed, true, stand_northeast());

  e->addAnimation("run_east", anim_speed, true, run_east());
  e->addAnimation("run_southeast", anim_speed, true, run_southeast());
  e->addAnimation("run_south", anim_speed, true, run_south());
  e->addAnimation("run_southwest", anim_speed, true, run_southwest());
  e->addAnimation("run_west", anim_speed, true, run_west());
  e->addAnimation("run_northwest", anim_speed, true, run_northwest());
  e->addAnimation("run_north", anim_speed, true, run_north());
  e->addAnimation("run_northeast", anim_speed, true, run_northeast());

  e->addAnimation("slide_east", anim_speed, false, slide_east());
  e->addAnimation("slide_southeast", anim_speed, false, slide_southeast());
  e->addAnimation("slide_south", anim_speed, false, slide_south());
  e->addAnimation("slide_southwest", anim_speed, false, slide_southwest());
  e->addAnimation("slide_west", anim_speed, false, slide_west());
  e->addAnimation("slide_northwest", anim_speed, false, slide_northwest());
  e->addAnimation("slide_north", anim_speed, false, slide_north());
  e->addAnimation("slide_northeast", anim_speed, false, slide_northeast());
}
}  // namespace player_animations
}  // namespace senseless_soccer
