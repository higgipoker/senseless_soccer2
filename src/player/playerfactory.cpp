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
#include "playerfactory.hpp"
#include "../player/player_animations.h"
#include "../team/kit.hpp"
#include "../team/tactics/position.hpp"

#include <gamelib2/engine/engine.hpp>
#include <gamelib2/game/game.hpp>
#include <gamelib2/utils/files.hpp>

namespace senseless_soccer {

PlayerFactory::PlayerFactory(gamelib2::Engine& in_engine,
                             gamelib2::Viewer& in_viewer)
    : engine(in_engine), viewer(in_viewer) {}

// -----------------------------------------------------------------------------
// makePlayer
// -----------------------------------------------------------------------------
Player* PlayerFactory::make_player(const std::string& name,
                                   gamelib2::Widget& in_parent) {
  std::unique_ptr<Player> player = std::make_unique<Player>();
  std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
  std::unique_ptr<Sprite> shadow = std::make_unique<Sprite>();

  player->create("player", name);
  sprite->init(Files::getWorkingDirectory() + "/gfx/player/player.png", 6, 24);
  sprite->clickable = true;
  sprite->anchor_type = AnchorType::ANCHOR_BASE_CENTER;
  player_animations::fill_animations(sprite.get());
  shadow->init(Files::getWorkingDirectory() + "/gfx/player/player_shadow.png",
               6, 24);
  shadow->anchor_type = AnchorType::ANCHOR_BASE_CENTER;
  shadow->z_order = -1;
  sprite->shadow = shadow.get();
  gamelib2::Game::connect(player.get(), sprite.get());

  in_parent.addChild(player->widget);
  in_parent.addChild(static_cast<Sprite*>(player->widget)->shadow);

  // this transfers ownership outside of the function
  PlayerEntity player_entity;
  player_entity.player = std::move(player);
  player_entity.sprite = std::move(sprite);
  player_entity.shadow = std::move(shadow);
  players.emplace_back(std::move(player_entity));

  return players.back().player.get();
}

void PlayerFactory::release_player(Player* player) {
  engine.remEntity(player);
  viewer.remWidget(player->widget);
  viewer.remWidget(static_cast<Sprite*>(player->widget)->shadow);
  for (auto it = players.begin(); it != players.end();) {
    if ((*it).player.get() == player) {
      players.erase(it);
    } else {
      ++it;
    }
  }
}

}  // namespace senseless_soccer
