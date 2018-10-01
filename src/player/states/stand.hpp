#pragma once
#include <gamelib2/types.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include "state.hpp"

namespace senseless_soccer {

class Stand : public State {
public:
    // specific constructor to get player pointer
    Stand(Player *context);

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

private:
    void face_ball();
};

} // namespace senseless_soccer
