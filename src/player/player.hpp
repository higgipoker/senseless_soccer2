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

#include "states/stand.hpp"
#include "states/run.hpp"

#include "../types.hpp"
#include "../joysticker/sensicontroller.hpp"
#include "../ball/ball.hpp"

#include <gamelib2/compass/compass.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/types.hpp>
#include <gamelib2/input/device.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

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

    // moved manually
    void onDragged(const Vector3 &diff) override;

    // controller interface
    void onControllerEvent(ControllerEvent event) override;

    // check if ball is under control
    bool ball_under_control();

    // attach an input
    void attachInput(SensiController *i);
    void detatchInput();

    // for sorting etc
    float distance_from_ball = 0;

    // shared ball
    static Ball *ball;

    // shirt number
    int shirt_number = 0;

    // the triangle defining short pass recipient possibilities
    Triangle short_pass_triangle;

protected:
    // state machine
    void change_state(const PlayerState &new_state);

    // helper to do the movement physics
    void do_physics(float dt);

    // knock the ball on
    void do_dribble();

    // control the ball
    void do_close_control();

    // kick the ball according to fire length
    void kick(const Vector3 &direction, unsigned int power);

    // an automatic short pass
    void short_pass(const Player *receiver);

    // handle when i get possession of the ball
    void on_got_possession();

    // handle when i lose possession of the ball
    void on_lost_possession();

    // track if in possession of ball
    bool in_possession = false;

    // track facing direction
    Compass facing;

    // save last direction
    Compass facing_old;

    // changed direction since last frame?
    bool changed_direction = true;

    // for dribble hit detection
    sf::CircleShape feet;

    // for close control detection
    sf::CircleShape control_inner;

    // lost control circle
    sf::CircleShape control_outer;

    // attached input
    SensiController *controller = nullptr;

    // don't control and shoot at the same time
    bool shooting = false;

    // map animations based on direction
    static std::map<Direction, std::string> stand_animation_map;
    static std::map<Direction, std::string> run_animation_map;

private:
    // states
    std::unique_ptr<Stand> stand_state;
    std::unique_ptr<Run> run_state;
    State *current_state = nullptr;

    // calc environment stuff
    void calc_short_pass_recipients();

    // define max and min kick powers
    const unsigned int min_pass_power = 30;
    const unsigned int max_pass_power = 100;

    // a lookup to define the precision of short pass strengths
    std::vector<unsigned int> short_pass_strenghts = {
      1,
      2,
      3,
    };

public:
    // for state machine pattern
    friend class State;
    friend class Stand;
    friend class Run;
};

} // namespace senseless_soccer
