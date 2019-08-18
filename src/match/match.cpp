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
Match::Match() : play(*this), enter_pitch(*this) { create("match", "match"); }

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Match::init(team::Team *t1, team::Team *t2, Pitch *p, Ball *b) {
  team1 = t1;
  team2 = t2;
  pitch = p;
  ball = b;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Match::step(float dt) {
  current_state->update(dt);
  if (current_state->finished()) {
    current_state->changeToNextState();
  }
}

// -----------------------------------------------------------------------------
// changeState
// -----------------------------------------------------------------------------
void Match::changeState(const MatchState next_state) {
  current_state->stop();
  switch (next_state) {
    case MatchState::EnterPitch:
      current_state = &enter_pitch;
      break;
    case MatchState::Kickoff:
      break;
    case MatchState::Play:
      current_state = &play;
      break;
    case MatchState::ThrowIn:
      break;
    case MatchState::Corner:
      break;
    case MatchState::GoalKick:
      break;
    case MatchState::FreeKick:
      break;
    case MatchState::Penalty:
      break;
  }
  current_state->start();

  for (auto &observer : observers) {
    observer->matchStateChanged(next_state);
  }
}

// -----------------------------------------------------------------------------
// observe
// -----------------------------------------------------------------------------
void Match::observe(MatchObserver *o) { observers.insert(o); }

// -----------------------------------------------------------------------------
// unObserve
// -----------------------------------------------------------------------------
void Match::unObserve(MatchObserver *o) { observers.erase(o); }

// -----------------------------------------------------------------------------
// ball_in_pitch
// -----------------------------------------------------------------------------
bool Match::ball_in_pitch() {
  if (ball->position.x - ball->circle.getRadius() <
      pitch->dimensions.bounds.left) {
    ball_out.pitch_side = Direction::WEST;
    return false;
  }
  if (ball->position.y - ball->circle.getRadius() <
      pitch->dimensions.bounds.top) {
    ball_out.pitch_end = Direction::NORTH;
    return false;
  }
  if (ball->position.x + ball->circle.getRadius() >
      pitch->dimensions.bounds.left + pitch->dimensions.bounds.width) {
    ball_out.pitch_side = Direction::EAST;
    return false;
  }
  if (ball->position.y + ball->circle.getRadius() >
      pitch->dimensions.bounds.top + pitch->dimensions.bounds.height) {
    ball_out.pitch_end = Direction::SOUTH;
    return false;
  }

  return true;
}

}  // namespace match
}  // namespace senseless_soccer
