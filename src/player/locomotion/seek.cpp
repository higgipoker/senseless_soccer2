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
#include "seek.hpp"
#include "../player.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Seek
// -----------------------------------------------------------------------------
Seek::Seek(Player *player)
  : Locomotion(player) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Seek::start() {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Seek::update(float _dt) {
    std::cout << "Stand" << std::endl;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void Seek::stop() {
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Seek::finished() {
    return false;
}
} // namespace senseless_soccer