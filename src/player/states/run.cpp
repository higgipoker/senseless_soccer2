#include "run.hpp"
#include "../player.hpp"
#include "stand.hpp"
#include <gamelib2/compass/compass.hpp>
#include <gamelib2/physics/collisions.hpp>

using namespace gamelib2;
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Run
// -----------------------------------------------------------------------------
Running::Running(Player &context)
  : State(context) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Running::start() {
    if (player.widget) {
        player.widget->startAnimation(
          Player::run_animation_map[player.facing.direction]);
    }
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Running::update(const float dt) {
    // close control or dribble
    if (player.changed_direction) {
        // change the running animation
        if (player.widget) {
            player.widget->startAnimation(
              Player::run_animation_map[player.facing.direction]);
        }

        // close control
        if (player.ball_under_control()) {
            player.do_close_control();
        }

    } else if (Collision::collides(player.feet, Player::ball->circle)) {
        if (!player.shooting) {
            player.do_dribble();
        }
    }
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Running::end() {
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Running::finished() {
    return (Floats::equal(player.velocity.magnitude2d(), 0));
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Running::changeToNextState() {
    player.change_state(PlayerState::Stand);
}

} // namespace senseless_soccer
