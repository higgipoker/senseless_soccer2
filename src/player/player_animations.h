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
#include <gamelib2/widgets/widget.hpp>
#include <vector>
namespace senseless_soccer {

static unsigned int anim_speed = 300000;
static gamelib2::Widget *sprite = nullptr;

static std::vector<unsigned int> stand_east() {
    std::vector<unsigned int> v;
    v.push_back(1);
    return v;
}

static std::vector<unsigned int> stand_southeast() {
    std::vector<unsigned int> v;
    v.push_back(4);
    return v;
}

static std::vector<unsigned int> stand_south() {
    std::vector<unsigned int> v;
    v.push_back(7);
    return v;
}

static std::vector<unsigned int> stand_southwest() {
    std::vector<unsigned int> v;
    v.push_back(10);
    return v;
}

static std::vector<unsigned int> stand_west() {
    std::vector<unsigned int> v;
    v.push_back(13);
    return v;
}

static std::vector<unsigned int> stand_northwest() {
    std::vector<unsigned int> v;
    v.push_back(16);
    return v;
}

static std::vector<unsigned int> stand_north() {
    std::vector<unsigned int> v;
    v.push_back(19);
    return v;
}

static std::vector<unsigned int> stand_northeast() {
    std::vector<unsigned int> v;
    v.push_back(22);
    return v;
}

static std::vector<unsigned int> run_east() {
    std::vector<unsigned int> v;
    v.push_back(0);
    v.push_back(1);
    return v;
}

static std::vector<unsigned int> run_southeast() {
    std::vector<unsigned int> v;
    v.push_back(3);
    v.push_back(5);
    return v;
}

static std::vector<unsigned int> run_south() {
    std::vector<unsigned int> v;
    v.push_back(6);
    v.push_back(8);
    return v;
}

static std::vector<unsigned int> run_southwest() {
    std::vector<unsigned int> v;
    v.push_back(9);
    v.push_back(11);
    return v;
}

static std::vector<unsigned int> run_west() {
    std::vector<unsigned int> v;
    v.push_back(12);
    v.push_back(13);
    return v;
}

static std::vector<unsigned int> run_northwest() {
    std::vector<unsigned int> v;
    v.push_back(15);
    v.push_back(17);
    return v;
}

static std::vector<unsigned int> run_north() {
    std::vector<unsigned int> v;
    v.push_back(18);
    v.push_back(20);
    return v;
}

static std::vector<unsigned int> run_northeast() {
    std::vector<unsigned int> v;
    v.push_back(21);
    v.push_back(23);
    return v;
}

static void fill_animations(gamelib2::Widget *spr) {
    sprite = spr;

    spr->addAnimation("stand_east", anim_speed, true, stand_east());
    spr->addAnimation("stand_southeast", anim_speed, true, stand_southeast());
    spr->addAnimation("stand_south", anim_speed, true, stand_south());
    spr->addAnimation("stand_southwest", anim_speed, true, stand_southwest());
    spr->addAnimation("stand_west", anim_speed, true, stand_west());
    spr->addAnimation("stand_northwest", anim_speed, true, stand_northwest());
    spr->addAnimation("stand_north", anim_speed, true, stand_north());
    spr->addAnimation("stand_northeast", anim_speed, true, stand_northeast());

    spr->addAnimation("run_east", anim_speed, true, run_east());
    spr->addAnimation("run_southeast", anim_speed, true, run_southeast());
    spr->addAnimation("run_south", anim_speed, true, run_south());
    spr->addAnimation("run_southwest", anim_speed, true, run_southwest());
    spr->addAnimation("run_west", anim_speed, true, run_west());
    spr->addAnimation("run_northwest", anim_speed, true, run_northwest());
    spr->addAnimation("run_north", anim_speed, true, run_north());
    spr->addAnimation("run_northeast", anim_speed, true, run_northeast());
}

} // namespace senseless_soccer
