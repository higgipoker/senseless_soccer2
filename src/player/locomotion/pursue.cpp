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
#include "pursue.hpp"
#include "../player.hpp"

#include <sstream>

namespace senseless_soccer {
namespace locomotion {

// -----------------------------------------------------------------------------
// Pursue
// -----------------------------------------------------------------------------
Pursue::Pursue(Player &p) : Locomotion(p, "pursue") {}

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Pursue::init(Entity *t) { target = t; }

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Pursue::start() { std::cout << "start pursue" << std::endl; }

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Pursue::update(float dt) {
  target->position.z = 0;

  // this will be normalised within player logic
  player.velocity = target->position - player.position;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void Pursue::stop() {
  std::cout << "stop retrieve" << std::endl;
  destination_reached = true;
  player.velocity.reset();
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Pursue::finished() { return false; }

// -----------------------------------------------------------------------------
// diagnosticParamaters
// -----------------------------------------------------------------------------
std::string Pursue::diagnosticParamaters() {
  std::stringstream s;
  s << "target: " << target->name;
  return s.str();
}

}  // namespace locomotion
}  // namespace senseless_soccer
