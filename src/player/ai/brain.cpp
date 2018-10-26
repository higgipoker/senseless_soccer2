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

std::map<std::string, State> Brain::state_map = {
    std::make_pair("idle", State::BrainIdle),
    std::make_pair("dribble", State::BrainDribble),
    std::make_pair("pass", State::BrainPass),
    std::make_pair("receivePass", State::BrainReceive),
    std::make_pair("retrieve", State::BrainRetrieve),
    std::make_pair("shoot", State::BrainShoot),
};

std::map<State, std::string> Brain::reverse_state_map = {
    std::make_pair(State::BrainIdle, "idle"),
    std::make_pair(State::BrainDribble, "dribble"),
    std::make_pair(State::BrainPass, "pass"),
    std::make_pair(State::BrainReceive, "receivePass"),
    std::make_pair(State::BrainRetrieve, "retrieve"),
    std::make_pair(State::BrainShoot, "shoot"),
};
// -----------------------------------------------------------------------------
// Brain
// -----------------------------------------------------------------------------
Brain::Brain(Player &p)
    : player(p), idle(*this), dribble(*this), receive_pass(*this), pass(*this),
      shoot(*this), retrieve(*this), locomotion(p) {
  locomotion.startStand();
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Brain::update(float dt) {
  current_state->update(dt);
  if (current_state->finished()) {
    current_state->stop();
    current_state->changeToNextState();
    current_state->start();
  }

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

  std::cout << "change state to " << reverse_state_map[state] << std::endl;

  current_state->stop();
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
  }
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
} // namespace ai
} // namespace senseless_soccer
