#pragma once

#include "state.hpp"

#include <gamelib2/types.hpp>
#include <gamelib2/widgets/sprite.hpp>
#include <gamelib2/utils/timer.hpp>

namespace senseless_soccer {

class Running : public State {
public:
  // specific constructor to get player pointer
  Running(Player &context);

  // state started
  void start() override;

  // main update
  void update(const float dt) override;

  // state over
  void end() override;

  // check for end state
  bool finished() override;

  // change to next state
  void changeToNextState() override;

private:
  // players cant do 60 dribble touches per second!
  gamelib2::Timer touch_timer;
  int ms_between_touches;
};

} // namespace senseless_soccer
