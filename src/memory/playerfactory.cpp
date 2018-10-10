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
#include <gamelib2/utils/files.hpp>
#include <gamelib2/widgets/sprite.hpp>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// makePlayer
// -----------------------------------------------------------------------------
std::unique_ptr<Player> PlayerFactory::makePlayer(const std::string &name) {
    // for gfx
    static const std::string dir = gamelib2::Files::getWorkingDirectory();
    static const std::string player_file = dir + "/gfx/player/player.png";
    static const std::string shadow_file =
      dir + "/gfx/player/player_shadow.png";

    // make the entity
    auto player = std::make_unique<Player>(name);

    // make a sprite for the player
    auto widget = std::make_unique<Sprite>(player_file, 6, 24);

    // get a pointer to derived class sprite
    auto sprite = static_cast<Sprite *>(widget.get());

    sprite->clickable = true;
    player_animations::fill_animations(sprite);

    // make a shadow for the sprite
    auto shadow = std::make_unique<Sprite>(shadow_file, 6, 24);
    shadow->z_order = -1;

    // sprite owns the shadow
    sprite->connectShadow(std::move(shadow));

    // entity owns the sprite
    player->connectWidget(std::move(widget));

    // sprite refers back to owning enity with weak pointer
    sprite->connectEntity(player.get());
    player->activate();
    return player;
}

} // namespace senseless_soccer
