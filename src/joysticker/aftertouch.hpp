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
#include "../ball/ball.hpp"
#include <gamelib2/input/controller.hpp>

using namespace gamelib2;
namespace senseless_soccer {

class Aftertouch {

public:
    Aftertouch(Controller &c);
    void start(Ball *b, const Vector3 &initial_normal, const float initial_mag);
    void end();
    void update();

private:
    Ball *ball = nullptr;
    Controller &controller;
    Vector3 aftertouch;
    Vector3 normal;
    Vector3 accumulated_aftertouch;
    Vector3 left;
    Vector3 right;
    Vector3 left_diagonal;
    Vector3 right_diagonal;
    Vector3 left_diagonal_reversed;
    Vector3 right_diagonal_reversed;
    Vector3 forward;
    Vector3 back;
    Vector3 neutral;

    bool accumulation_applied = false;
    float initial_force = 0;
    unsigned int ticks = 0;
};

} // namespace senseless_soccer
