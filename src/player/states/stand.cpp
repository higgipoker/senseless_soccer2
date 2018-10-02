#include "stand.hpp"
#include "../player.hpp"
#include "run.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Stand::Stand(Player &context)
  : State(context) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Stand::start() {
    face_ball();
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Stand::update(const float _dt) {
    face_ball();
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Stand::end() {
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Stand::finished() {
    return (gamelib2::Floats::greater_than(player.velocity.magnidude2d(), 0));
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Stand::changeToNextState() {
    player.change_state(PlayerState::Run);
}

// -----------------------------------------------------------------------------
// face_ball
// -----------------------------------------------------------------------------
void Stand::face_ball() {
    if (player.widget) {
        if (player.ball) {

            gamelib2::Vector3 to_ball = player.ball->position - player.position;
            gamelib2::Compass c(to_ball.normalise());
            player.widget->startAnimation(
              player.stand_animation_map[c.direction]);
        }
    }
}
} // namespace senseless_soccer
