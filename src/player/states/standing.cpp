#include "standing.hpp"
#include "../player.hpp"
#include "running.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Standing::Standing(Player &context) : State(context, "standing") {}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Standing::start() { player.face_ball(); }

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Standing::update(const float dt) { State::update(dt); }

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Standing::end() {}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Standing::finished() {
  return (gamelib2::Floats::greater_than(player.velocity.magnitude2d(), 0)) ||
         player.jumping || player.sliding;
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Standing::changeToNextState() {
  if (player.sliding) {
    player.change_state(PlayerState::Slide);
  } else if (player.jumping) {
    player.change_state(PlayerState::Jump);
  } else if (gamelib2::Floats::greater_than(player.velocity.magnitude2d(), 0)) {
    player.change_state(PlayerState::Run);
  }
}
} // namespace senseless_soccer
