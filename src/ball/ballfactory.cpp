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

#include <gamelib2/math/vector.hpp>
#include <gamelib2/utils/files.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include <iostream>

using namespace gamelib2;
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// make_ball
// -----------------------------------------------------------------------------
void BallFactory::make_ball(Ball *ball, Sprite *sprite, Sprite *shadow) {
  std::string working_dir = Files::getWorkingDirectory();
  std::string gfx_path = working_dir + "/gfx/";

  ball->create("ball", "ball");
  sprite->init(gfx_path + "ball_new.png", 4, 2);
  sprite->z_order = 10;
  shadow->init(gfx_path + "ball_shadow.png", 1, 1);
  sprite->clickable = true;
  shadow->z_order = -1;
  sprite->shadow = shadow;
  Game::connect(ball, sprite);
  ball_animations::fill_animations(ball);
  ball->startAnimation("roll");
}

}  // namespace senseless_soccer
