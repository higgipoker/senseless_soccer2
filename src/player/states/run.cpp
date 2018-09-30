#include "run.hpp"
#include "../player.hpp"
#include "stand.hpp"
#include <gamelib2/compass/compass.hpp>
#include <gamelib2/physics/collisions.hpp>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Run
// -----------------------------------------------------------------------------
Run::Run(Player *context)
  : State(context) {
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Run::start() {
    auto w = player->widget.lock();
    w->startAnimation(player->run_animation_map[player->facing.direction]);
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Run::update(const float _dt) {
    if (player->changed_direction) {
        auto w = player->widget.lock();
        w->startAnimation(player->run_animation_map[player->facing.direction]);
    }

    // dribble?
    if (gamelib2::Collision::collides(player->feet, player->ball->circle)) {
        player->ball->kick(player->velocity.normalise() * player->speed * 100);
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
    return (player->velocity.magnidude2d() <= 0);
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Run::changeToNextState() {
    std::unique_ptr<gamelib2::State> state(new Stand(player));
    player->ChangeState(state);
}

} // namespace senseless_soccer
