#pragma once
#include <gamelib2/statemachine/state.hpp>
#include <gamelib2/types.hpp>
#include <gamelib2/widgets/sprite.hpp>
#include <gamelib2/input/controller.hpp>

namespace senseless_soccer {

using namespace gamelib2;
class Player;
class State : public gamelib2::State {
public:
    // specific constructor to get player pointer
    State(Player &context);

    // state started
    void start() override;

    // main update
    void update(const float _dt) override;

    // state over
    void end() override;

    // check for end state
    bool finished() override;

    // change to next state
    void changeToNextState() override;

    // event handler
    bool handle_input(ControllerEvent event);

protected:
    // pointer back to player for state machine
    Player &player;

    // quick access to the widget
    Widget &sprite;
};

} // namespace senseless_soccer
