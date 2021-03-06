#pragma once
#include <gamelib2/input/device.hpp>
#include <gamelib2/statemachine/state.hpp>
#include <gamelib2/types.hpp>
#include <gamelib2/widgets/sprite.hpp>

namespace senseless_soccer {

using namespace gamelib2;
class Player;
class State : public gamelib2::State {
public:
  // specific constructor to get player pointer
  State(Player &context, std::string n);

  // must have virt dest
  virtual ~State() override = default;

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

  // event handler
  void handle_input(const ControllerEvent &event) override;

  // when the input changes to this player
  virtual void on_controller_handover();

  // a string name for debug
  std::string name;

protected:
  // pointer back to player for state machine
  Player &player;

  // quick access to the widget
  Widget &sprite;

  // lock dpad if fire pressed ef
  bool lock_dpad = false;
};

} // namespace senseless_soccer
