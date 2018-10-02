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
#include "ball_factory.hpp"
#include "ball.hpp"
#include "ball_animations.hpp"
#include <gamelib2/utils/files.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include <iostream>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// makePlayer
// -----------------------------------------------------------------------------
void BallFactory::makeBall(const std::string &name,
                           std::shared_ptr<gamelib2::Entity> &entity,
                           std::shared_ptr<gamelib2::Widget> &sprite,
                           std::shared_ptr<gamelib2::Widget> &shadow) {
    // for gfx
    std::string working_dir = gamelib2::Files::getWorkingDirectory();

    // make the entity
    entity = std::make_shared<Ball>(name);

    // make a sprite for the ball
    sprite = std::make_shared<gamelib2::Sprite>(
      working_dir + "/gfx/ball_new.png", 4, 2);
    std::cout << sprite.use_count() << std::endl;
    sprite->clickable = true;
    ball_animations::fill_animations(sprite.get());

    // make a shadow for the sprite
    shadow = std::make_shared<gamelib2::Sprite>(
      working_dir + "/gfx/ball_shadow.png", 1, 1);

    auto spr = dynamic_cast<gamelib2::Sprite *>(sprite.get());
    spr->connectShadow(shadow);

    entity->connectWidget(sprite);
    sprite->connectEntity(entity);
    entity->activate();
    sprite->startAnimation("roll");
}

} // namespace senseless_soccer
