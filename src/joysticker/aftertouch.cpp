/****************************************************************************
 * CopyRight (c) 2018 P. Higgins
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
#include "aftertouch.hpp"
#include <iostream>

namespace senseless_soccer {

static const int MODIFIER_FULL = 10;
static const int MODIFIER_HALF = 20;

static const int LIFT_FORWARD = -10;
static const int LIFT_NEUTRAL = 10;
static const int LIFT_REVERSE = 30;

static const int APPLY_AFTERTOUCH_DELAY = 10;
static const int MAX_AFTERTOUCH_TIME = 500;

//  --------------------------------------------------
//  init static members
//  --------------------------------------------------
Ball *Aftertouch::ball = nullptr;
Controller *Aftertouch::controller = nullptr;
unsigned int Aftertouch::ticks = 0;
Vector3 Aftertouch::normal;
Vector3 Aftertouch::accumulated_aftertouch;
bool Aftertouch::accumulation_applied = false;

using std::cout;
using std::endl;
//  --------------------------------------------------
//  constructor
//  --------------------------------------------------
Aftertouch::Aftertouch() {
}

//  --------------------------------------------------
//  start aftertouch handling
//  --------------------------------------------------
void Aftertouch::startAftertouch(Ball *b, Controller *c,
                                 const Vector3 &initial_normal) {
    ball = b;
    controller = c;
    normal = initial_normal;
    normal = normal.normalizeToUnits();
    normal.z = 0;
    accumulation_applied = false;
    ticks = 0;

    cout << "start aftertouch" << endl;
}

//  --------------------------------------------------
//  end aftertouch handling
//  --------------------------------------------------
void Aftertouch::endAftertouch() {
    ticks = 0;
    ball = nullptr;
    controller = nullptr;

    cout << "end aftertouch" << endl;
}

//  --------------------------------------------------
//  Update
//  --------------------------------------------------
void Aftertouch::update() {
    // don't start yet
    if (ball == nullptr || controller == nullptr) {
        return;
    }

    Vector3 dpad;
    Vector3 aftertouch;

    if (controller->input.states[Up])
        dpad.y = -1;

    if (controller->input.states[Down])
        dpad.y = 1;

    if (controller->input.states[Left])
        dpad.x = -1;

    if (controller->input.states[Right])
        dpad.x = 1;

    normal.z = 0;

    // get Left pointing vector
    Vector3 left = normal.perpendicular();
    left = left.normalizeToUnits();

    // get Right pointing vector
    Vector3 right = left.reverse();

    // get Left diagonal vector
    Vector3 left_diagonal = normal + left;
    left_diagonal = left_diagonal.normalizeToUnits();

    // get Right diagonal vector
    Vector3 right_diagonal = normal + right;
    right_diagonal = right_diagonal.normalizeToUnits();

    // get the reverse vectors (for lift)
    Vector3 left_diagonal_reversed = right_diagonal.reverse();
    Vector3 right_diagonal_reversed = left_diagonal.reverse();

    Vector3 forward = normal;
    Vector3 back = forward.reverse();
    Vector3 neutral;

    if (ticks >= APPLY_AFTERTOUCH_DELAY && !accumulation_applied) {
        accumulation_applied = true;
        aftertouch = accumulated_aftertouch;
        accumulated_aftertouch.reset();
    }

    // apply Left aftertouch
    if (dpad.equals(left)) {
        if (ticks > APPLY_AFTERTOUCH_DELAY)
            aftertouch += (left * MODIFIER_FULL);
        else
            accumulated_aftertouch += (left * MODIFIER_FULL);
    }

    // apply Right aftertouch
    else if (dpad.equals(right)) {
        if (ticks > APPLY_AFTERTOUCH_DELAY)
            aftertouch += (right * MODIFIER_FULL);
        else
            accumulated_aftertouch += (right * MODIFIER_FULL);
    }

    // apply Left-diagonal aftertouch
    else if (dpad.equals(left_diagonal)) {
        if (ticks > APPLY_AFTERTOUCH_DELAY)
            aftertouch += (left * MODIFIER_HALF);
        else
            accumulated_aftertouch += (left * MODIFIER_HALF);
    }

    // apply Right-diagonal aftertouch
    else if (dpad.equals(right_diagonal)) {
        if (ticks > APPLY_AFTERTOUCH_DELAY)
            aftertouch += (right * MODIFIER_HALF);
        else
            accumulated_aftertouch += (right * MODIFIER_HALF);
    }

    // apply Left diagonal reversed for lift
    else if (dpad.equals(left_diagonal_reversed)) {
        if (ticks > APPLY_AFTERTOUCH_DELAY)
            aftertouch += (left * MODIFIER_HALF);
        else
            accumulated_aftertouch += (left * MODIFIER_HALF);
    }

    // apply Right diagonal reversed for lift
    else if (dpad.equals(right_diagonal_reversed)) {
        if (ticks > APPLY_AFTERTOUCH_DELAY)
            aftertouch += (right * MODIFIER_HALF);
        else
            accumulated_aftertouch += (right * MODIFIER_HALF);
    }

    // now do the pure lift
    if (ticks > APPLY_AFTERTOUCH_DELAY) {
        if (dpad.equals(neutral)) {
            if (ticks > APPLY_AFTERTOUCH_DELAY) {
                aftertouch.z += LIFT_NEUTRAL;
            } else {
                accumulated_aftertouch.z += LIFT_NEUTRAL;
            }
        } else if (dpad.equals(forward)) {
            if (ticks > APPLY_AFTERTOUCH_DELAY) {
                aftertouch.z += LIFT_FORWARD;
            } else {
                accumulated_aftertouch.z += LIFT_FORWARD;
            }
        } else {
            // reversed for high
            if (dpad.equals(back)) {
                if (ticks > APPLY_AFTERTOUCH_DELAY) {
                    aftertouch.z += LIFT_REVERSE;
                } else {
                    accumulated_aftertouch.z += LIFT_REVERSE;
                }
            }
        }
    }

    // apply aftertouch to ball
    ball->aftertouch(aftertouch);

    // end condition
    if (++ticks > MAX_AFTERTOUCH_TIME) {
        endAftertouch();
    } else {
        //        if (dpad.equals(forward))
        //        {
        //            print("aftertouch forward");
        //        }
        //
        //        if (dpad.equals(back))
        //        {
        //            print("aftertouch back");
        //        }
        //
        //        if (dpad.equals(Left))
        //        {
        //            print("aftertouch Left");
        //        }
        //
        //        if (dpad.equals(Right))
        //        {
        //            print("aftertouch Right");
        //        }
    }
}
} // namespace senseless_soccer
