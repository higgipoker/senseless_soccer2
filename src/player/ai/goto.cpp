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
#include "goto.hpp"
#include "../player.hpp"
#include "brain.hpp"

namespace senseless_soccer {
namespace ai {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GoTo::GoTo(Brain &b) : BrainState(b, "GoTo") {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoTo::start() { brain.locomotion.startSeek(target); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoTo::init(const gamelib2::Vector3 &t) { target = t; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoTo::stop() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool GoTo::finished() { return brain.player.position.equals(target, 0); }

// -----------------------------------------------------------------------------
// a
// aaa
// -----------------------------------------------------------------------------
void GoTo::update(float dt) {}

}  // namespace ai
}  // namespace senseless_soccer
