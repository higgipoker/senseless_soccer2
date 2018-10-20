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
#include "sensicontroller.hpp"
#include "../ball/ball.hpp"
#include "../player/player.hpp"
#include <gamelib2/utils/files.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

using namespace gamelib2;
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// SensiController
// -----------------------------------------------------------------------------
SensiController::SensiController(InputDevice &i)
  : Controller(i)
  , label(Files::getWorkingDirectory() + "/fonts/swos.ttf") // todo font factory
  , aftertouch(*this) {

    label.setSize(14);
    label.setColor(sf::Color::White);

} // namespace senseless_soccer

// -----------------------------------------------------------------------------
// attachToPlayer
// -----------------------------------------------------------------------------
void SensiController::attachToPlayer(Player *p) {
    if (p == player)
        return;

    if (player) {
        player->detatchInput();
    }
    player = p;
    if (player) {
        player->attachInput(this);
        label.setText(p->shirt_number);
    }
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void SensiController::update() {
    Controller::update();
    aftertouch.update();

    // attached to a player?
    if (player) {
        auto rect = player->widget->bounds();
        label.setCenter(static_cast<unsigned int>(rect.left + rect.width / 2),
                        static_cast<unsigned int>(rect.top + rect.width / 2 -
                                                  rect.height / 2 - 4));
    }
}

// -----------------------------------------------------------------------------
// startAftertouch
// -----------------------------------------------------------------------------
void SensiController::startAftertouch(Ball *b, const Vector3 &normal,
                                      const float initial_mag) {
    aftertouch.start(b, normal, initial_mag);
}

// -----------------------------------------------------------------------------
// stopAftertouch
// -----------------------------------------------------------------------------
void SensiController::stopAftertouch() {
    aftertouch.end();
}

} // namespace senseless_soccer
