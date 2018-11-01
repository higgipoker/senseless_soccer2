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
#include <gamelib2/utils/files.hpp>

namespace senseless_soccer {
namespace team {

std::map<std::string, std::shared_ptr<Position>> Position::positions;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Position::Position(std::string fn) : filename(std::move(fn)) {
  gamelib2::File file(filename);

  auto lines = file.getLines("//");

  if (lines.size() > 1) {
    name = lines[0];
    for (unsigned int i = 1; i < lines.size(); i++) {
      std::string str = lines[i];
      std::size_t pos = str.find(':');
      std::string first = str.substr(0, pos);
      std::string second = str.substr(pos + 1);
      sectors.push_back(atoi(first.c_str()));
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Position::scanPositions() {
  // already scanned
  if (positions.empty()) {
    auto files = gamelib2::Files::getFilesInFolder(
        gamelib2::Files::getWorkingDirectory() + "/data/positions");

    for (auto filename : files) {
      auto position = std::make_shared<Position>(filename);
      positions.insert(std::make_pair(position->name, position));

      std::cout << "found position: " << position->name << std::endl;
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
  }

  return sectors[ball_sector];
}
}  // namespace team
}  // namespace senseless_soccer
