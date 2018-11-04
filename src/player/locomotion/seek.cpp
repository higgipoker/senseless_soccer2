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
#include "seek.hpp"
#include "../player.hpp"

namespace senseless_soccer {
namespace locomotion {

// -----------------------------------------------------------------------------
// Seek
// -----------------------------------------------------------------------------
Seek::Seek(Player &player) : Locomotion(player, "seek") {}

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Seek::init(const Vector3 &t) { target = t; }
// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Seek::start() {
  target.z = 0;

  // this will be normalised within player logic
  player.velocity = target - player.position;
  distance = (target - player.position).magnitude();
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Seek::update(float dt) {
  float new_distance = (target - player.position).magnitude();

  if (new_distance > distance) {
    player.velocity = target - player.position;
  }

  distance = new_distance;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void Seek::stop() { player.velocity.reset(); }

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Seek::finished() { return player.position.equals(target, 5.f); }
}  // namespace locomotion
}  // namespace senseless_soccer
