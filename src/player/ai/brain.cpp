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
#include "brain.hpp"
#include "../player.hpp"

namespace senseless_soccer {
namespace ai {

// debug
std::map<std::string, State> Brain::state_map = {
    std::make_pair("idle", State::BrainIdle),
    std::make_pair("dribble", State::BrainDribble),
    std::make_pair("pass", State::BrainPass),
    std::make_pair("receivePass", State::BrainReceive),
    std::make_pair("retrieve", State::BrainRetrieve),
    std::make_pair("shoot", State::BrainShoot),
    std::make_pair("slide", State::BrainSlide),
    std::make_pair("jump", State::BrainJump),
    std::make_pair("cover", State::BrainCover),
};

// debug
std::map<State, std::string> Brain::reverse_state_map = {
    std::make_pair(State::BrainIdle, "idle"),
    std::make_pair(State::BrainDribble, "dribble"),
    std::make_pair(State::BrainPass, "pass"),
    std::make_pair(State::BrainReceive, "receivePass"),
    std::make_pair(State::BrainRetrieve, "retrieve"),
    std::make_pair(State::BrainShoot, "shoot"),
    std::make_pair(State::BrainJump, "jump"),
    std::make_pair(State::BrainGoTo, "go to"),
    std::make_pair(State::BrainCover, "cover"),
};

// -----------------------------------------------------------------------------
// Brain
// -----------------------------------------------------------------------------
Brain::Brain(Player &p)
    : player(p),
      idle(*this),
      dribble(*this),
      receive_pass(*this),
      pass(*this),
      shoot(*this),
      retrieve(*this),
      slide(*this),
      jump(*this),
      go(*this),
      cover(*this),
      locomotion(p) {
  locomotion.startStand();
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Brain::update(float dt) {
  // update brain state machine
  current_state->update(dt);
  if (current_state->finished()) {
    current_state->stop();
    changeState(next_state);
    current_state->start();
  }

  // player locomotion
  locomotion.update(dt);
}

// -----------------------------------------------------------------------------
// handleMessage
// -----------------------------------------------------------------------------
void Brain::message(const std::string &msg) {
  if (msg == "receive") {
    changeState(State::BrainReceive);
  } else if (msg == "dribble") {
    locomotion.startStand();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Brain::changeState(const State state) {
  // stop ----------------------------------------
  current_state->stop();

  // change --------------------------------------
  switch (state) {
    case State::BrainIdle:
      current_state = &idle;
      break;
    case State::BrainDribble:
      current_state = &dribble;
      break;
    case State::BrainPass:
      current_state = &pass;
      break;
    case State::BrainShoot:
      current_state = &shoot;
      break;
    case State::BrainReceive:
      current_state = &receive_pass;
      break;
    case State::BrainRetrieve:
      current_state = &retrieve;
      break;
    case State::BrainSlide:
      current_state = &slide;
      break;
    case State::BrainJump:
      current_state = &jump;
      break;
    case State::BrainGoTo:
      current_state = &go;
      break;
    case State::BrainCover:
      current_state = &cover;
      break;
  }

  // start ---------------------------------------
  current_state->start();
}

// -----------------------------------------------------------------------------
// currentState
// -----------------------------------------------------------------------------
std::string Brain::currentState() { return current_state->name; }

// -----------------------------------------------------------------------------
// onControllerAttached
// -----------------------------------------------------------------------------
void Brain::onControllerAttached() { current_state->stop(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Brain::goTo(const Vector3 &target) {
  go.init(target);
  changeState(State::BrainGoTo);
}
}  // namespace ai
}  // namespace senseless_soccer
