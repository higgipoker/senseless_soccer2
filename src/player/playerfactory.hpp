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

#include "../player/player.hpp"
#include <gamelib2/game/game.hpp>
namespace senseless_soccer {

struct PlayerEntity {
  std::unique_ptr<Player> player;
  std::unique_ptr<Sprite> sprite;
  std::unique_ptr<Sprite> shadow;
};

class PlayerFactory {
 public:
    PlayerFactory(gamelib2::Engine &in_engine, gamelib2::Viewer &in_viewer);
  // makes a player
  Player* make_player(const std::string& name, gamelib2::Widget &in_parent);
  void release_player(Player* player);

 private:
  gamelib2::Engine &engine;
  gamelib2::Viewer &viewer;
  std::vector<PlayerEntity> players;
};
}  // namespace senseless_soccer
