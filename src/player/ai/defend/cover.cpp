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
#include "cover.hpp"
#include "../../../team/tactics/position.hpp"
#include "../../player.hpp"
#include "../brain.hpp"

namespace senseless_soccer {
namespace ai {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Cover::Cover(Brain &b) : BrainState(b, "cover") {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Cover::start() {
  pitch = brain.player.my_team->pitch;
  if (pitch) {
    grid = &pitch->grid;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Cover::stop() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Cover::finished() { return false; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Cover::update(float dt) {
  if (auto pitch = brain.player.my_team->pitch) {
    auto grid = pitch->grid;
    int ball_sector = grid.getSector(Player::ball->position);

    // only recalculate if ball is in a different sector
    if (ball_sector != last_sector) {
      last_sector = ball_sector;

      int player_sector =
          brain.player.role->target(team::Situation::Play, ball_sector);

      // rotate sectors for attacking south goal
      if (brain.player.my_team->side == Direction::NORTH) {
        ball_sector = grid.mirrorSector(ball_sector);
        player_sector =
            brain.player.role->target(team::Situation::Play, ball_sector);
        player_sector = grid.mirrorSector(player_sector);
      }

      brain.locomotion.startSeek(grid.getRandoPointInSector(player_sector));
    }
  }
}
}  // namespace ai
}  // namespace senseless_soccer
