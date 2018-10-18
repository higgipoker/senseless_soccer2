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
#include "pursue.hpp"
#include "../player.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Pursue
// -----------------------------------------------------------------------------
Pursue::Pursue(Player *p)
  : Locomotion(p) {
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Pursue::init(const Vector3 &static_target, const Vector3 *dynamic_target) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Pursue::start() {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Pursue::update(float _dt) {
    Vector3 destination = *target;
    destination.z = 0;

    // this will be normalised within player logic
    player->velocity = destination - player->position;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void Pursue::stop() {
    destination_reached = true;
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Pursue::finished() {
    return destination_reached;
}

} // namespace senseless_soccer
