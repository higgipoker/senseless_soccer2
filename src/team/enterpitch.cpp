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
EnterPitch::EnterPitch(Team &t) : State(t) { next_state = TeamState::LineUp; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::start() {
  if (team.players.empty()) return;
  // set up some line up positions
  offset.x = team.players[0]->widget->bounds().left * 2;
  first_position = team.pitch.lock()->dimensions.center;
  first_position.x -= offset.x * team.players.size() / 2;
  if (team.side == Direction::NORTH) {
    first_position.y -= vertical_offset;
  } else {
    first_position.y += vertical_offset;
  }

  last_position = first_position;
  last_position += offset * team.players.size();

  // init marchers
  for (auto &player : team.players) {
    player->setPosition(team.pitch.lock()->dimensions.bounds.left +
                            team.pitch.lock()->dimensions.bounds.width,
                        last_position.y);
    marchers.push(player);
  }
  march_player();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::stop() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool EnterPitch::finished() {
  for (auto player : team.players) {
    if (player->velocity.magnitude()) {
      return false;
    }
  }
  if (++end_ticks >= end_delay) {
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::update(float dt) {
  if (++ticks > speed) {
    ticks = 0;
    march_player();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void EnterPitch::march_player() {
  if (!marchers.empty()) {
    Player *player = marchers.front();
    marchers.pop();

    if (auto pitch = team.pitch.lock()) {
      player->brain.goTo(last_position);
      last_position -= offset;
    }
  }
}

}  // namespace team
}  // namespace senseless_soccer
