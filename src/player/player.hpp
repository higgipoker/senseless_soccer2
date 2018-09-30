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

#include <gamelib2/compass/compass.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/input/keyboardlistener.hpp>
#include <gamelib2/statemachine/state_machine.hpp>
#include <gamelib2/types.hpp>
#include <memory>

namespace senseless_soccer {

class Player : public gamelib2::Entity, gamelib2::StateMachine {
public:
    // construct with an entity name
    Player(std::string in_name);

    // main update
    void update(float dt) override;

    // only activate after sprite is connected!
    void activate() override;

    // helper to init the animatio map
    static void Init();

protected:
    // hook for states to react to state changed
    void on_change_state() override;

    // helper to do the movement physics
    void do_physics(float dt);

    // track facing direction
    gamelib2::Compass facing;

    // save last direction
    gamelib2::Compass facing_old;

    // changed direction since last frame?
    bool changed_direction = true;

    // map animations based on running direction
    static std::map<gamelib2::Direction, std::string> stand_animation_map;
    static std::map<gamelib2::Direction, std::string> run_animation_map;

public:
    // for state machine pattern
    friend class Stand;
    friend class Run;
};

} // namespace senseless_soccer
