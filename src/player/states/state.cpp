#include "state.hpp"
#include "../player.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// State
// -----------------------------------------------------------------------------
State::State(Player &context)
  : player(context)
  , sprite(*player.widget) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void State::start() {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void State::update(const float _dt) {
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void State::end() {
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool State::finished() {
    return false;
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void State::changeToNextState() {
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
bool State::handle_input(ControllerEvent event) {
    switch (event.id) {
    case Fire:
        if (event.status == Pressed) {
        } else {

            if (player.ball_under_control()) {
                Vector3 kick_force =
                  (player.facing.toVector() * event.param * 2000);
                player.kick(kick_force);
            }
        }
        break;

    case DPadLeft:
        if (event.status == Pressed) {
            player.velocity.x = -1;
        } else {
            if (Floats::equal(player.velocity.x, -1)) {
                player.velocity.x = 0;
            }
        }
        break;

    case DPadRight:
        if (event.status == Pressed) {
            player.velocity.x = 1;
        } else {
            if (Floats::equal(player.velocity.x, 1)) {
                player.velocity.x = 0;
            }
        }
        break;

    case DPadUp:
        if (event.status == Pressed) {
            player.velocity.y = -1;
        } else {
            if (Floats::equal(player.velocity.y, -1)) {
                player.velocity.y = 0;
            }
        }
        break;

    case DPadDown:
        if (event.status == Pressed) {
            player.velocity.y = 1;
        } else {
            if (Floats::equal(player.velocity.y, 1)) {
                player.velocity.y = 0;
            }
        }
        break;

    case NoEvent:
        break;
    }

    return false;
}

} // namespace senseless_soccer
