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
    if (player->changed_direction) {
        sf::CircleShape control = player->feet;
        control.setRadius(control.getRadius() * 2);
        if (Collision::collides(control, player->ball.lock()->circle)) {
            player->do_close_control();
        }

    } else if (Collision::collides(player->feet, player->ball.lock()->circle)) {
        player->do_dribble();
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
    return (Floats::equal(player->velocity.magnidude2d(), 0));
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Run::changeToNextState() {
    player->change_state(PlayerState::Stand);
}

} // namespace senseless_soccer
