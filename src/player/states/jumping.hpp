#pragma once
#include <gamelib2/types.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include "state.hpp"

namespace senseless_soccer {

class Jumping : public State {
public:
  // specific constructor to get player pointer
  Jumping(Player &context);

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

  // handle input
  void handle_input(const ControllerEvent &event) override;

private:
  // how quickly the player gets up after the slide
  int recover_frames = 60;

  // in the recovery (getting up) phase
  bool getting_up = false;

  // tmp
  float max_height = 2.5f;
  bool going_up = true;
};

} // namespace senseless_soccer
