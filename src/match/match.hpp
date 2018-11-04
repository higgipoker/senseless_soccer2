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
#include "play.hpp"
#include "state.hpp"

#include "../ball/ball.hpp"
#include "../pitch/pitch.hpp"

#include <gamelib2/compass/compass.hpp>
#include <gamelib2/game/entity.hpp>

#include <memory>
#include <set>
#include <utility>

namespace senseless_soccer {
namespace team {
class Team;
}
namespace match {

enum class MatchState { Play };

class MatchObserver {
 public:
  virtual void matchStateChanged(const MatchState new_state) = 0;

 private:
};

class Match : public gamelib2::Entity {
 public:
  Match();
  void init(const std::shared_ptr<team::Team> &t1,
            const std::shared_ptr<team::Team> &t2,
            const std::shared_ptr<Pitch> &p, const std::shared_ptr<Ball> &b);
  void update(float dt);
  void changeState(const MatchState next_state);
  void observe(MatchObserver *o);
  void unObserve(MatchObserver *o);

  std::shared_ptr<team::Team> team1;
  std::shared_ptr<team::Team> team2;
  std::shared_ptr<Pitch> pitch;
  std::shared_ptr<Ball> ball;

 private:
  Play play;
  State *current_state = &play;
  std::set<MatchObserver *> observers;

  // check ballin pitch conditions
  bool ball_in_pitch();
  std::pair<gamelib2::Direction, gamelib2::Direction> ball_out_side;

 public:
  friend class State;
  friend class Play;
};
}  // namespace match
}  // namespace senseless_soccer
