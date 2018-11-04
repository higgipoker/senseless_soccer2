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
#include "match.hpp"

#include "../team/team.hpp"

namespace senseless_soccer {
namespace match {

// -----------------------------------------------------------------------------
// Match
// -----------------------------------------------------------------------------
Match::Match() : gamelib2::Entity("match", "match"), play(*this) {}

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Match::init(const std::shared_ptr<team::Team> &t1,
                 const std::shared_ptr<team::Team> &t2,
                 const std::shared_ptr<Pitch> &p,
                 const std::shared_ptr<Ball> &b) {
  team1 = t1;
  team2 = t2;
  pitch = p;
  ball = b;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Match::update(float dt) {
  // state machine
  current_state->update(dt);
  if (current_state->finished()) {
    current_state->changeToNextState();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Match::changeState(const MatchState next_state) {
  current_state->stop();
  switch (next_state) {
    case MatchState::Play:
      break;
  }
  current_state->start();

  for (auto &observer : observers) {
    observer->matchStateChanged(next_state);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Match::observe(MatchObserver *o) { observers.insert(o); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Match::unObserve(MatchObserver *o) { observers.erase(o); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Match::ball_in_pitch() {
  if (ball->position.x - ball->circle.getRadius() <
      pitch->dimensions.bounds.left) {
    ball_out_side.first = Direction::WEST;
    return false;
  }
  if (ball->position.y - ball->circle.getRadius() <
      pitch->dimensions.bounds.top) {
    ball_out_side.second = Direction::NORTH;
    return false;
  }
  if (ball->position.x + ball->circle.getRadius() >
      pitch->dimensions.bounds.left + pitch->dimensions.bounds.width) {
    ball_out_side.first = Direction::EAST;
    return false;
  }
  if (ball->position.y + ball->circle.getRadius() >
      pitch->dimensions.bounds.top + pitch->dimensions.bounds.height) {
    ball_out_side.second = Direction::SOUTH;
    return false;
  }

  return true;
}

}  // namespace match
}  // namespace senseless_soccer
