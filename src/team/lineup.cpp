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
#include "lineup.hpp"
#include "../player/player.hpp"
#include "team.hpp"
namespace senseless_soccer {
namespace team {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
LineUp::LineUp(Team &t) : State(t) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void LineUp::start() {
  if (team.players.empty()) return;

  marchers = {};
  // init marchers
  for (const auto &player : team.players) {
    marchers.push(player);
  }
  march_player();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void LineUp::stop() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool LineUp::finished() {
  for (const auto &player : team.players) {
    if (auto p = player.lock()) {
      if (p->velocity.magnitude()) {
        return false;
      }
    }
  }
  return true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void LineUp::update(float dt) {
  if (++ticks > speed) {
    ticks = 0;
    march_player();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void LineUp::march_player() {
  if (!marchers.empty()) {
    auto player = marchers.front();
    marchers.pop();

    if (auto pitch = team.pitch) {
      if (auto p = player.lock()) {
        int player_sector = p->role->target(team::Situation::KickOff, 0);

        // rotate sectors for attacking south goal
        if (team.side == Direction::NORTH) {
          player_sector = team.pitch->grid->mirrorSector(player_sector);
        }

        p->brain.goTo(team.pitch->grid->getRandoPointInSector(player_sector));
      }
    }
  }
}

}  // namespace team
}  // namespace senseless_soccer
