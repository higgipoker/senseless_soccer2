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
#include <gamelib2/types.hpp>
#include <gamelib2/input/input.hpp>
#include <memory>

#include "../ball/ball.hpp"
#include "states/stand.hpp"
#include "states/run.hpp"

using namespace gamelib2;
namespace senseless_soccer {

enum class PlayerState { Stand, Run };

class Run;
class Stand;
class Player : public Entity, public ControllerListener {
public:
    // construct with an entity name
    Player(std::string in_name);

    // main update
    void update(float dt) override;

    // only activate after sprite is connected!
    void activate() override;

    // helper to init the animatio map
    static void Init();

    // movedmanually
    void onMoved(const Vector3 &new_position, float dx = 0,
                 float dy = 0) override;

    // controller interface
    void onControllerEvent(ControllerEvent event) override;

    // shared ball
    static Ball *ball;

protected:
    // state machine
    void change_state(const PlayerState &new_state);

    // helper to do the movement physics
    void do_physics(float dt);

    // knock the ball on
    void do_dribble();

    // control the ball
    void do_close_control();

    // kick the ball
    void kick(Vector3 force);

    // track facing direction
    Compass facing;

    // save last direction
    Compass facing_old;

    // changed direction since last frame?
    bool changed_direction = true;

    // for collisions
    sf::CircleShape feet;

    // attached input
    Input *input = nullptr;

    // map animations based on direction
    static std::map<Direction, std::string> stand_animation_map;
    static std::map<Direction, std::string> run_animation_map;

private:
    // states
    std::unique_ptr<Stand> stand_state;
    std::unique_ptr<Run> run_state;
    State *current_state = nullptr;

public:
    // for state machine pattern
    friend class State;
    friend class Stand;
    friend class Run;
};

} // namespace senseless_soccer
