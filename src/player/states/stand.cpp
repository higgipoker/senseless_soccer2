#include "stand.hpp"
#include "../player.hpp"
#include "run.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Standing::Standing(Player &context)
  : State(context) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Standing::start() {
    player.face_ball();
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Standing::update(const float _dt) {
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Standing::end() {
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Standing::finished() {
    return (gamelib2::Floats::greater_than(player.velocity.magnitude2d(), 0));
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Standing::changeToNextState() {
    player.change_state(PlayerState::Run);
}
} // namespace senseless_soccer
