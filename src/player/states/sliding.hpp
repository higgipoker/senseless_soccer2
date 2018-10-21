#pragma once
#include <gamelib2/types.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include "state.hpp"

namespace senseless_soccer {

class Sliding : public State {
public:
				// specific constructor to get player pointer
				Sliding(Player &context);

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
};

} // namespace senseless_soccer
