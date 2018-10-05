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
Run::Run(Player &context)
  : State(context) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Run::start() {
    if (player.widget) {
        player.widget->startAnimation(
          player.run_animation_map[player.facing.direction]);
    }
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Run::update(const float _dt) {

    // dribble or close control
    if (player.changed_direction) {
        // change the running animation
        if (player.widget) {
            player.widget->startAnimation(
              player.run_animation_map[player.facing.direction]);
        }

        // close control
        if (player.ball_under_control()) {
            player.do_close_control();
        }

    } else if (Collision::collides(player.feet, player.ball->circle)) {
        if (!player.shooting) {
            player.do_dribble();
        }
    }
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Run::end() {
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Run::finished() {
    return (Floats::equal(player.velocity.magnidude2d(), 0));
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Run::changeToNextState() {
    player.change_state(PlayerState::Stand);
}

} // namespace senseless_soccer
