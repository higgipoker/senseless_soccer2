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

#include "../locomotion/locomotionmanager.hpp"
#include "attack/dribble.hpp"
#include "attack/pass.hpp"
#include "attack/receivepass.hpp"
#include "attack/shoot.hpp"
#include "brainstate.hpp"
#include "defend/slide.hpp"
#include "idle.hpp"
#include "jump.hpp"
#include "retrieve.hpp"

#include <map>

namespace senseless_soccer {
class Player;
namespace ai {

// list of brainstates
enum class State {
  BrainIdle,
  BrainDribble,
  BrainPass,
  BrainShoot,
  BrainReceive,
  BrainRetrieve,
  BrainSlide,
  BrainJump,
};

class Brain {
public:
  Brain(Player &p);
  void update(float dt);
  void message(const std::string &msg);
  void changeState(const State state);
  void onControllerAttached();

  locomotion::LocomotionManager locomotion;

  // distnostic map
  static std::map<std::string, State> state_map;
  static std::map<State, std::string> reverse_state_map;
  std::string currentState();

private:
  Player &player;
  State next_state = State::BrainIdle;

  Idle idle;
  Dribble dribble;
  Pass pass;
  ReceivePass receive_pass;
  Retrieve retrieve;
  Shoot shoot;
  Slide slide;
  Jump jump;
  BrainState *current_state = &idle;

public:
  // state machine pattern
  friend class Idle;
  friend class Pass;
  friend class Shoot;
  friend class ReceivePass;
  friend class Retrieve;
  friend class Dribble;
  friend class Slide;
  friend class Jump;
};
} // namespace ai
} // namespace senseless_soccer
