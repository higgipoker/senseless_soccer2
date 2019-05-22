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
#include "positionfactory.hpp"
#include <gamelib2/utils/file.hpp>
#include <gamelib2/utils/files.hpp>

namespace senseless_soccer {
namespace team {
std::map<std::string, Position> PositionFactory::positions;
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void PositionFactory::scanPositions() {
  // already scanned
  if (positions.empty()) {
    auto dir = gamelib2::Files::getWorkingDirectory() + "/data/positions";
    auto files = gamelib2::Files::getFilesInFolder(dir);

    for (auto &filename : files) {
      Position position;
      position.loadFromFile(filename);
      positions.insert(std::make_pair(position.name, position));
      std::cout << "found position: " << position.name << std::endl;
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Position *PositionFactory::getPosition(const std::string &_in_name) {
  if (positions.empty()) {
    scanPositions();
  }
  return &positions[_in_name];
}

}  // namespace team
}  // namespace senseless_soccer
