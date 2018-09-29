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
#include "player_animations.h"
#include <gamelib2/graphics/sprite.hpp>
#include <gamelib2/utils/files.hpp>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// makePlayer
// -----------------------------------------------------------------------------
std::shared_ptr<Player> PlayerFactory::makePlayer(const std::string &name) {
    // for gfx
    std::string working_dir = gamelib2::Files::getWorkingDirectory();

    // make a sprite for the player
    std::shared_ptr<gamelib2::Widget> sprite =
      std::make_shared<gamelib2::Sprite>(working_dir + "/gfx/player/player.png",
                                         6, 24);
    sprite->clickable = true;
    fill_animations(sprite.get());
    auto player = std::make_shared<Player>(name);
    player->connectWidget(sprite);
    sprite->connectEntity(player);
    return player;
}

} // namespace senseless_soccer
