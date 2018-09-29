#include "stand.hpp"
#include "../player.hpp"
#include "run.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Stand::Stand(Player *context)
  : State(context) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Stand::start() {
    sprite->startAnimation("stand_south");
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Stand::update(const float _dt) {
    if (player->velocity.magnidude2d() > 0) {
        std::unique_ptr<gamelib2::State> state(new Run(player));
        player->ChangeState(state);
    }
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
    return (player->velocity.magnidude2d() > 0);
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Stand::changeToNextState() {
    std::unique_ptr<gamelib2::State> state(new Run(player));
    player->ChangeState(state);
}

} // namespace senseless_soccer
