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

static const float SPIN_FACTOR = 100;

// lift
static const float LIFT_FORWARD = 0;
static const float LIFT_NEUTRAL = 0;
static const float LIFT_REVERSE = 0;

// left or right
static const float MODIFIER_FULL = 0;

// diagonals
static const float MODIFIER_HALF = 0;

// delay (give initial conditions time)
static const int WAIT = 10;

// time to read for aftertouch (frames) based on 120fps, 12 frames = 100ms
static const int MAX_AFTERTOUCH_TIME = 50;

using std::cout;
using std::endl;

// -----------------------------------------------------------------------------
// construct
// -----------------------------------------------------------------------------
Aftertouch::Aftertouch(Controller &c) : controller(c) {}

// -----------------------------------------------------------------------------
//  start aftertouch handling
// -----------------------------------------------------------------------------
void Aftertouch::start(Ball *b, const Vector3 &normal, const float mag) {
  ball = b;

  // sets up the left, right vectors etc
  set_dpad();
  set_vectors(normal);

  topspin.z = 800;

  ball->addTopSpin(topspin);
  topspin.reset();
  sidespin.reset();
}

// -----------------------------------------------------------------------------
//  end aftertouch handling
// -----------------------------------------------------------------------------
void Aftertouch::end() {
  ticks = 0;
  ball = nullptr;
  topspin.reset();
  sidespin.reset();
}

// -----------------------------------------------------------------------------
//  Update
// -----------------------------------------------------------------------------
void Aftertouch::update() {
  if (ball == nullptr) {
    return;
  }

  //    if (++ticks < WAIT) {
  //        return;
  //    }

  set_dpad();

  if (dpad_left()) {
    sidespin += (left * SPIN_FACTOR);
  }

  if (dpad_right()) {
    sidespin += (right * SPIN_FACTOR);
  }

  if (dpad_forward()) {
    // topspin.z -= (SPIN_FACTOR * 0.5f);
  }

  if (dpad_back()) {
    topspin.z += (SPIN_FACTOR * 0.5f);
  }

  if (dpad_neutral()) {
    topspin.z += (SPIN_FACTOR * 0.2f);
  }

  // apply aftertouch to ball
  ball->addSideSpin(sidespin);
  ball->addTopSpin(topspin);

  topspin.reset();
  sidespin.reset();

  // end condition
  if (++ticks > MAX_AFTERTOUCH_TIME) {
    end();
  }
}

// -----------------------------------------------------------------------------
// set_vectors
// -----------------------------------------------------------------------------
void Aftertouch::set_vectors(Vector3 normal) {
  normal = normal;
  normal = normal.normalizeToUnits();
  normal.z = 0;
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
}

// -----------------------------------------------------------------------------
// set_dpad
// -----------------------------------------------------------------------------
void Aftertouch::set_dpad() {
  dpad.reset();
  if (controller.input.states[Up])
    dpad.y = -1;

  if (controller.input.states[Down])
    dpad.y = 1;

  if (controller.input.states[Left])
    dpad.x = -1;

  if (controller.input.states[Right])
    dpad.x = 1;
}

// -----------------------------------------------------------------------------
// dpad_forward
// -----------------------------------------------------------------------------
bool Aftertouch::dpad_forward() {
  return (dpad.equals(forward) || dpad.equals(left_diagonal) ||
          dpad.equals(right_diagonal));
}

// -----------------------------------------------------------------------------
// dpad_back
// -----------------------------------------------------------------------------
bool Aftertouch::dpad_back() {
  return (dpad.equals(back) || dpad.equals(left_diagonal_reversed) ||
          dpad.equals(right_diagonal_reversed));
}

// -----------------------------------------------------------------------------
// dpad_left
// -----------------------------------------------------------------------------
bool Aftertouch::dpad_left() {
  return (dpad.equals(left) || dpad.equals(left_diagonal) ||
          dpad.equals(left_diagonal_reversed));
}

// -----------------------------------------------------------------------------
// dpad_right
// -----------------------------------------------------------------------------
bool Aftertouch::dpad_right() {
  return (dpad.equals(right) || dpad.equals(right_diagonal) ||
          dpad.equals(right_diagonal_reversed));
}

// -----------------------------------------------------------------------------
// dpad_neutral
// -----------------------------------------------------------------------------
bool Aftertouch::dpad_neutral() {
  return (dpad.equals(Vector3(0, 0, 0)) || dpad.equals(left) ||
          dpad.equals(right));
}
} // namespace senseless_soccer
