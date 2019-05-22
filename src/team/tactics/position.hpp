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
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace senseless_soccer {
namespace team {

// possible match situations
enum class Situation { Play, KickOff, GoalKick, Corner };

// offsets for match situation sectors
const static int total_sectors = 285;
const static int index_offset_attacking = 0;
const static int index_offset_play = 0;
const static int index_offset_kickoff = total_sectors;
const static int index_offset_goalkick = index_offset_kickoff + 1;
const static int index_offset_corner = index_offset_goalkick + 1;
const static int index_offset_defending = index_offset_corner + 1;

class Position {
 public:
  void loadFromFile(const std::string &in_file);
  std::string name;

  int target(const Situation s, const int ball_sector);

 protected:
  std::vector<int> sectors;
  std::string filename;
};
}  // namespace team
}  // namespace senseless_soccer
