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

#include <SFML/Graphics/CircleShape.hpp>
#include <gamelib2/compass/compass.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/input/controller.hpp>
#include <gamelib2/statemachine/state_machine.hpp>
#include <gamelib2/types.hpp>
#include <memory>

#include "../ball/ball.hpp"
#include "states/stand.hpp"
#include "states/run.hpp"

using namespace gamelib2;
namespace senseless_soccer {

enum class PlayerState { Stand, Run };

class Run;
class Stand;
class Player : public gamelib2::Entity, public ControllerListener {
public:
    // construct with an entity name
    Player(std::string in_name);
    ~Player() = default;

    // main update
    void update(float dt) override;

    // only activate after sprite is connected!
    void activate() override;

    // helper to init the animatio map
    static void Init();

    // movedmanually
    void onMoved(const gamelib2::Vector3 &new_position, float dx = 0,
                 float dy = 0) override;

    // controller interface
    void onControllerEvent(ControllerEvent event) override;

    // shared ball
    static std::weak_ptr<Ball> ball;

protected:
    // state machine
    void change_state(const PlayerState &new_state);

    // helper to do the movement physics
    void do_physics(float dt);

    // knock the ball on
    void do_dribble();

    // control the ball
    void do_close_control();

    // track facing direction
    gamelib2::Compass facing;

    // save last direction
    gamelib2::Compass facing_old;

    // changed direction since last frame?
    bool changed_direction = true;

    // for collisions
    sf::CircleShape feet;

    // map animations based on running direction
    static std::map<gamelib2::Direction, std::string> stand_animation_map;
    static std::map<gamelib2::Direction, std::string> run_animation_map;

private:
    // states
    std::unique_ptr<Stand> stand_state;
    std::unique_ptr<Run> run_state;
    gamelib2::State *current_state = nullptr;

public:
    // for state machine pattern
    friend class State;
    friend class Stand;
    friend class Run;
};

} // namespace senseless_soccer
