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

#include "ai/attack/pass.hpp"
#include "ai/brain.hpp"
#include "ai/defend/cover.hpp"
#include "ai/defend/slide.hpp"
#include "states/jumping.hpp"
#include "states/running.hpp"
#include "states/sliding.hpp"
#include "states/standing.hpp"
#include "states/state.hpp"

#include "../ball/ball.hpp"
#include "../joysticker/sensicontroller.hpp"
#include "../pitch/pitch.hpp"
#include "../team/tactics/position.hpp"
#include "../team/team.hpp"

#include <gamelib2/compass/compass.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/input/device.hpp>
#include <gamelib2/types.hpp>

#include <SFML/Graphics.hpp>

#include <memory>

using namespace gamelib2;
namespace senseless_soccer {

enum class PlayerState { Stand, Run, Slide, Jump };
namespace team {
class Team;
}

class Player : public Entity, public ControllerListener {
 public:
  // construct
  Player();

  // destruct
  virtual ~Player();

  // main update
  void step(float dt) override;

  // moved manually
  void onDragged(const Vector3 &diff) override;

  // controller interface
  void onControllerEvent(ControllerEvent event) override;

  // check if ball is under control
  bool ball_under_control();

  // attach an input
  void attachInput(SensiController *i);

  // detatch input
  void detatchInput();

  // set my team
  void setTeam(team::Team *t);

  // get current state name
  std::string stateName();

  // trigger a state manually
  void triggerState(const PlayerState state);

  // playing position (role)
  void setRole(team::Position *in_role);

  // ai
  ai::Brain brain;

  // for sorting etc
  float distance_from_ball = 0;

  // shared ball among all players
  static Ball *ball;

  // players need to know about the pitch
  static Pitch *pitch;

  // shirt number
  int shirt_number = 0;

  // the triangle defining short pass recipient possibilities
  Triangle short_pass_triangle;

  // suspend input temporarily
  bool input_suspended = false;

  // attached input
  SensiController *controller = nullptr;

  // debug display
  sf::VertexArray debug_short_pass;

  // track facing direction
  Compass facing;

  // testing
  team::Position *role = nullptr;

  // helper to init the animation map
  static void init();

 protected:
  // add perspective to the ball
  void perspectivize(float camera_height) override;

  // state machine
  void change_state(const PlayerState &new_state);

  // helper to do the movement physics
  void do_physics(float dt);

  // knock the ball on
  void do_dribble();

  // control the ball
  void do_close_control();

  // kick the ball according to fire length
  void kick(const Vector3 &direction, int power);

  // an automatic short pass
  void short_pass();

  // shoot at goal
  void shoot();

  // slide for a slide tackile
  void slide();

  // jump for a header
  void jump();

  // handle when i get possession of the ball
  void on_got_possession();

  // handle when i lose possession of the ball
  void on_lost_possession();

  // work out the best short pass candidate
  Player *calc_short_pass_receiver();

  // track if in possession of ball
  bool in_possession = false;

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

  // don't control and shoot at the same time
  bool shooting = false;

  // tmp solution?
  bool sliding = false;
  bool jumping = false;

  // map animations based on direction
  static std::map<Direction, std::string> standmap;
  static std::map<Direction, std::string> runmap;
  static std::map<Direction, std::string> slidemap;

 private:
  // states
  Standing stand_state;
  Running run_state;
  Sliding slide_state;
  Jumping jump_state;
  State *current_state = &stand_state;

  // current team i play on
  team::Team *my_team = nullptr;

  // calc environment stuff
  void calc_short_pass_recipients();
  void face_ball();

  // define max and min kick powers
  const int min_pass_power = 30;
  const int max_pass_power = 500;

  // a lookup to define the precision of short pass strengths
  std::vector<int> short_pass_strenghts = {
      1,
      2,
      3,
  };

 public:
  // for state machine pattern
  friend class State;
  friend class Standing;
  friend class Running;
  friend class Sliding;
  friend class Jumping;
  friend class ai::Pass;
  friend class ai::Shoot;
  friend class ai::Slide;
  friend class ai::Jump;
  friend class ai::Cover;
  friend class Locomotion;
  friend class locomotion::Stand;
  friend class team::Team;
};

}  // namespace senseless_soccer
