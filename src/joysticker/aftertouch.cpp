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

// base trajectory with no aftertouch applied
static const float INITIAL_TRAJECTORY = 0.16f;

// lift
static const int LIFT_FORWARD = 0;
static const int LIFT_NEUTRAL = 0;
static const int LIFT_REVERSE = 0;

// left or right
static const int MODIFIER_FULL = 0;

// diagonals
static const int MODIFIER_HALF = 0;

// restrictions
static const int APPLY_AFTERTOUCH_DELAY = 0;
static const int MAX_AFTERTOUCH_TIME = 30;

using std::cout;
using std::endl;

// -----------------------------------------------------------------------------
// construct
// -----------------------------------------------------------------------------
Aftertouch::Aftertouch(Controller &c)
  : controller(c) {
}

// -----------------------------------------------------------------------------
//  start aftertouch handling
// -----------------------------------------------------------------------------
void Aftertouch::start(Ball *b, const Vector3 &initial_normal,
                       const float initial_mag) {
    ball = b;
    normal = initial_normal;
    normal = normal.normalizeToUnits();
    normal.z = 0;
    accumulation_applied = false;
    ticks = 0;

    normal.z = 0;

    // get Left pointing vector
    left = normal.perpendicular();
    left = left.normalizeToUnits();

    // get Right pointing vector
    right = left.reverse();

    // get Left diagonal vector
    left_diagonal = normal + left;
    left_diagonal = left_diagonal.normalizeToUnits();

    // get Right diagonal vector
    right_diagonal = normal + right;
    right_diagonal = right_diagonal.normalizeToUnits();

    // get the reverse vectors (for lift)
    left_diagonal_reversed = right_diagonal.reverse();
    right_diagonal_reversed = left_diagonal.reverse();

    forward = normal;
    back = forward.reverse();

    aftertouch.z += INITIAL_TRAJECTORY * initial_mag;
    ball->aftertouch(aftertouch);

    cout << "start aftertouch, " << initial_mag << endl;
}

// -----------------------------------------------------------------------------
//  end aftertouch handling
// -----------------------------------------------------------------------------
void Aftertouch::end() {
    ticks = 0;
    ball = nullptr;
    accumulated_aftertouch.reset();

    cout << "end aftertouch" << endl;
}

// -----------------------------------------------------------------------------
//  Update
// -----------------------------------------------------------------------------
void Aftertouch::update() {
    if (ball == nullptr) {
        return;
    }

    Vector3 dpad;

    if (controller.input.states[Up])
        dpad.y = -1;

    if (controller.input.states[Down])
        dpad.y = 1;

    if (controller.input.states[Left])
        dpad.x = -1;

    if (controller.input.states[Right])
        dpad.x = 1;

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
            cout << "FORWARD" << endl;
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
        end();
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
