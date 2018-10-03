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
        std::cout << "FIRE ";
        if (event.status == Pressed) {
            std::cout << "Pressed" << std::endl;
        } else {

            //            if (player.ball_under_control()) {
            Vector3 kick_force =
              (player.facing.toVector() * event.param * 2000);
            // kick_force.z = kick_force.magnitude() * 0.2f;
            player.kick(kick_force);
            //            }
        }
        break;

    case DPadLeft:
        std::cout << "DPAD_LEFT ";
        if (event.status == Pressed) {
            player.velocity.x = -1;
            std::cout << "Pressed" << std::endl;
        } else {
            if (Floats::equal(player.velocity.x, -1)) {
                player.velocity.x = 0;
            }
            std::cout << "Released" << std::endl;
        }
        break;

    case DPadRight:
        std::cout << "DPAD_RIGHT ";
        if (event.status == Pressed) {
            player.velocity.x = 1;
            std::cout << "Pressed" << std::endl;
        } else {
            if (Floats::equal(player.velocity.x, 1)) {
                player.velocity.x = 0;
            }
            std::cout << "Released" << std::endl;
        }
        break;

    case DPadUp:
        std::cout << "DPAD_UP ";
        if (event.status == Pressed) {
            player.velocity.y = -1;
            std::cout << "Pressed" << std::endl;
        } else {
            if (Floats::equal(player.velocity.y, -1)) {
                player.velocity.y = 0;
            }
            std::cout << "Released" << std::endl;
        }
        break;

    case DPadDown:
        std::cout << "DPAD_DOWN ";
        if (event.status == Pressed) {
            player.velocity.y = 1;
            std::cout << "Pressed" << std::endl;
        } else {
            if (Floats::equal(player.velocity.y, 1)) {
                player.velocity.y = 0;
            }
            std::cout << "Released" << std::endl;
        }
        break;

    case NoEvent:
        break;
    }

    return false;
}

} // namespace senseless_soccer
