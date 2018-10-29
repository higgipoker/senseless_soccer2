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
#include "enterpitch.hpp"
#include "../player/player.hpp"
#include "team.hpp"
namespace senseless_soccer {
namespace team {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
EnterPitch::EnterPitch(Team &t) : State(t) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::start() {
  // initial position of all players
  int x = 250;
  int y = 250;
  for (auto &player : team.players) {
    player->setPosition(x, y);
    x += 30;
    y += 30;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::stop() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool EnterPitch::finished() { return false; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::update(float dt) {}

} // namespace team
} // namespace senseless_soccer
