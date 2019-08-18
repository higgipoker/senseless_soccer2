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
#include <gamelib2/game/entity.hpp>
#include <vector>
namespace senseless_soccer {
namespace ball_animations {
const float anim_speed = 0.01f * 10.0f;

static const std::vector<int> frames{0, 1, 2, 3, 4, 5, 6};

/**
 * @brief fill_animations
 * @param e
 */
static void fill_animations(gamelib2::Entity *e) {
  e->addAnimation("roll", anim_speed, true, frames);
}

}  // namespace ball_animations
}  // namespace senseless_soccer
