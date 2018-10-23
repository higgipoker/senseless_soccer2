#include "sliding.hpp"
#include "../player.hpp"

#include <gamelib2/physics/collisions.hpp>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Sliding::Sliding(Player &context) : State(context, "sliding") {}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Sliding::start() {
  if (Floats::equal(player.velocity.magnitude(), 0)) {
    player.velocity = player.facing.toVector();
  }
  player.speed = 300;
  if (player.widget) {
    player.widget->startAnimation(
        Player::slide_animation_map[player.facing.direction]);
  }
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Sliding::update(const float _dt) {
  if (Collision::collides(player.feet, Player::ball->circle)) {
    if (!player.shooting) {
      player.kick(player.facing.toVector(), 1);
    }
  }

  if (player.widget->currentAnimation()->finished()) {
    getting_up = true;
    player.velocity.reset();
  }
  if (getting_up) {
    recover_frames--;
  }
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Sliding::end() {
  player.speed = 150;
  player.velocity.reset();
  recover_frames = 60;
  getting_up = false;

  if (player.controller) {
    on_controller_handover();
  }
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Sliding::finished() { return recover_frames == 0; }

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Sliding::changeToNextState() {
  player.sliding = false;
  player.change_state(PlayerState::Stand);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Sliding::handle_input(const ControllerEvent &event) {}
} // namespace senseless_soccer
