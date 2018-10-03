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
std::vector<Ball*> BallFactory::balls;

void BallFactory::destroy(){
	for(auto &ball : balls){
		Sprite *sprite = static_cast<Sprite*> (ball->widget);
		delete sprite->shadow;
		delete ball->widget;
		delete ball;
	}
}


// -----------------------------------------------------------------------------
// makePlayer
// -----------------------------------------------------------------------------
Ball *BallFactory::makeBall(const std::string &name) {
    // for gfx
    std::string working_dir = gamelib2::Files::getWorkingDirectory();

    // make the entity
    Ball *ball = new Ball(name);

    // make a sprite for the player
    auto *sprite = new Sprite(working_dir + "/gfx/ball_new.png", 4, 2);
    sprite->clickable = true;
    ball_animations::fill_animations(sprite);

    // make a shadow for the sprite
    Sprite *shadow = new Sprite(working_dir + "/gfx/ball_shadow.png", 1, 1);
    shadow->z_order = -1;

    // connect everyting together
    sprite->connectShadow(shadow);
    sprite->connectEntity(ball);
    ball->connectWidget(sprite);
    ball->activate();
    balls.emplace_back(ball);
    return ball;
}

} // namespace senseless_soccer
