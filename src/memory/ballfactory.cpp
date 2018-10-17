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
#include "ballfactory.hpp"
#include "../ball/ball.hpp"
#include "../ball/ball_animations.hpp"
#include <gamelib2/utils/files.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include <iostream>

using namespace gamelib2;
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// makePlayer
// -----------------------------------------------------------------------------
std::unique_ptr<Ball> BallFactory::makeBall(const std::string &name) {
    // for gfx
    static const std::string working_dir =
      gamelib2::Files::getWorkingDirectory();
    static const std::string ball_file = working_dir + "/gfx/ball_new.png";
    static const std::string ball_shadow_file =
      working_dir + "/gfx/ball_shadow.png";

    // make the entity
    std::unique_ptr<Ball> ball = std::make_unique<Ball>(name);

    // make a sprite for the player
    std::unique_ptr<Widget> widget = std::make_unique<Sprite>(ball_file, 4, 2);

    // get a pointer to derived class sprite
    auto sprite = dynamic_cast<Sprite *>(widget.get());
    sprite->z_order = 10;

    sprite->clickable = true;
    ball_animations::fill_animations(sprite);

    // make a shadow for the sprite
    auto shadow = std::make_unique<Sprite>(ball_shadow_file, 1, 1);
    shadow->z_order = -1;

    // entity owns the sprite
    ball->connectWidget(std::move(widget));

    // sprite owns the shadow
    sprite->connectShadow(std::move(shadow));

    // sprite has raw "look at" pointer back to entity
    sprite->connectEntity(ball.get());
    sprite->startAnimation("roll");
    ball->activate();
    return ball;
}

} // namespace senseless_soccer
