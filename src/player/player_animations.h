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
#include <gamelib2/widgets/sprite.hpp>
#include <vector>
namespace senseless_soccer {
namespace player_animations {
static int anim_speed = 10;

// -----------------------------------------------------------------------------
// standing animations
// -----------------------------------------------------------------------------
static std::vector<int> stand_east() {
  std::vector<int> v;
  v.push_back(1);
  return v;
}
static std::vector<int> stand_southeast() {
  std::vector<int> v;
  v.push_back(4);
  return v;
}
static std::vector<int> stand_south() {
  std::vector<int> v;
  v.push_back(7);
  return v;
}
static std::vector<int> stand_southwest() {
  std::vector<int> v;
  v.push_back(10);
  return v;
}
static std::vector<int> stand_west() {
  std::vector<int> v;
  v.push_back(13);
  return v;
}
static std::vector<int> stand_northwest() {
  std::vector<int> v;
  v.push_back(16);
  return v;
}
static std::vector<int> stand_north() {
  std::vector<int> v;
  v.push_back(19);
  return v;
}

static std::vector<int> stand_northeast() {
  std::vector<int> v;
  v.push_back(22);
  return v;
}

// -----------------------------------------------------------------------------
// running animations
// -----------------------------------------------------------------------------
static std::vector<int> run_east() {
  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  return v;
}
static std::vector<int> run_southeast() {
  std::vector<int> v;
  v.push_back(3);
  v.push_back(5);
  return v;
}
static std::vector<int> run_south() {
  std::vector<int> v;
  v.push_back(6);
  v.push_back(8);
  return v;
}
static std::vector<int> run_southwest() {
  std::vector<int> v;
  v.push_back(9);
  v.push_back(11);
  return v;
}
static std::vector<int> run_west() {
  std::vector<int> v;
  v.push_back(12);
  v.push_back(13);
  return v;
}
static std::vector<int> run_northwest() {
  std::vector<int> v;
  v.push_back(15);
  v.push_back(17);
  return v;
}

static std::vector<int> run_north() {
  std::vector<int> v;
  v.push_back(18);
  v.push_back(20);
  return v;
}
static std::vector<int> run_northeast() {
  std::vector<int> v;
  v.push_back(21);
  v.push_back(23);
  return v;
}

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
  std::vector<int> v;
  v.push_back(27);
  v.push_back(28);
  for (int i = 0; i < 2; ++i) v.push_back(29);
  return v;
}
static std::vector<int> slide_south() {
  std::vector<int> v;
  v.push_back(30);
  v.push_back(31);
  for (int i = 0; i < 2; ++i) v.push_back(32);
  return v;
}
static std::vector<int> slide_southwest() {
  std::vector<int> v;
  v.push_back(33);
  v.push_back(34);
  for (int i = 0; i < 2; ++i) v.push_back(35);
  return v;
}
static std::vector<int> slide_west() {
  std::vector<int> v;
  v.push_back(36);
  v.push_back(37);
  for (int i = 0; i < 2; ++i) v.push_back(38);
  return v;
}
static std::vector<int> slide_northwest() {
  std::vector<int> v;
  v.push_back(39);
  v.push_back(40);
  for (int i = 0; i < 2; ++i) v.push_back(41);
  return v;
}

static std::vector<int> slide_north() {
  std::vector<int> v;
  v.push_back(42);
  v.push_back(43);
  for (int i = 0; i < 2; ++i) v.push_back(44);
  return v;
}
static std::vector<int> slide_northeast() {
  std::vector<int> v;
  v.push_back(45);
  v.push_back(46);
  for (int i = 0; i < 2; ++i) v.push_back(47);
  return v;
}

static void fill_animations(Sprite *spr) {
  spr->addAnimation("stand_east", anim_speed, true, stand_east());
  spr->addAnimation("stand_southeast", anim_speed, true, stand_southeast());
  spr->addAnimation("stand_south", anim_speed, true, stand_south());
  spr->addAnimation("stand_southwest", anim_speed, true, stand_southwest());
  spr->addAnimation("stand_west", anim_speed, true, stand_west());
  spr->addAnimation("stand_northwest", anim_speed, true, stand_northwest());
  spr->addAnimation("stand_north", anim_speed, true, stand_north());
  spr->addAnimation("stand_northeast", anim_speed, true, stand_northeast());

  spr->addAnimation("run_east", anim_speed, true, run_east());
  spr->addAnimation("run_southeast", anim_speed, true, run_southeast());
  spr->addAnimation("run_south", anim_speed, true, run_south());
  spr->addAnimation("run_southwest", anim_speed, true, run_southwest());
  spr->addAnimation("run_west", anim_speed, true, run_west());
  spr->addAnimation("run_northwest", anim_speed, true, run_northwest());
  spr->addAnimation("run_north", anim_speed, true, run_north());
  spr->addAnimation("run_northeast", anim_speed, true, run_northeast());

  spr->addAnimation("slide_east", anim_speed, false, slide_east());
  spr->addAnimation("slide_southeast", anim_speed, false, slide_southeast());
  spr->addAnimation("slide_south", anim_speed, false, slide_south());
  spr->addAnimation("slide_southwest", anim_speed, false, slide_southwest());
  spr->addAnimation("slide_west", anim_speed, false, slide_west());
  spr->addAnimation("slide_northwest", anim_speed, false, slide_northwest());
  spr->addAnimation("slide_north", anim_speed, false, slide_north());
  spr->addAnimation("slide_northeast", anim_speed, false, slide_northeast());
}
}  // namespace player_animations
}  // namespace senseless_soccer
