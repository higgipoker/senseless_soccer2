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
#include "position.hpp"
#include <gamelib2/utils/file.hpp>

namespace senseless_soccer {
namespace team {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Position::loadFromFile(const std::string &in_file) {
  gamelib2::File file(in_file);

  auto lines = file.getLines("//");

  if (lines.size() > 1) {
    name = lines[0];
    for (unsigned int i = 1; i < lines.size(); i++) {
      std::string str = lines[i];
      std::size_t pos = str.find(':');
      std::string first = str.substr(0, pos);
      sectors.push_back(atoi(first.c_str()));
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int Position::target(const Situation s, const int ball_sector) {
  switch (s) {
    case Situation::Play:
      return sectors[ball_sector + index_offset_play];
      break;

    case Situation::KickOff:
      return sectors[index_offset_kickoff];
      break;

    case Situation::GoalKick:
      break;

    case Situation::Corner:
      break;
  }

  return sectors[ball_sector];
}
}  // namespace team
}  // namespace senseless_soccer
