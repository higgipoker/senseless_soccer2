#include "jumping.hpp"
#include "../player.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/physics/collisions.hpp>

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Jumping::Jumping(Player &context) : State(context, "jumping") {}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Jumping::start() {
  // hack do not end immediately!
  player.position.z = 1;

  if (Floats::equal(player.velocity.magnitude(), 0)) {
    player.velocity = player.facing.toVector();
  }
  player.speed = 200;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Jumping::update(const float dt) {
  if (Collision::collides(player.feet, Player::ball->circle)) {
    if (!player.shooting) {
      player.kick(player.facing.toVector(), 1);
    }
  }

  if (going_up) {
    player.velocity.z = 8;
  } else {
    player.velocity.z = -10;
  }

  if (Floats::greater_than(player.position.z, max_height)) {
    going_up = false;
  }

  if (Floats::less_than(player.position.z, 0)) {
    player.position.z = 0;
  }
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Jumping::end() {
  going_up = true;
  player.velocity.reset();
  player.position.z = 0;
  player.speed = 150;

  if (player.controller) {
    on_controller_handover();
  }
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Jumping::finished() { return Floats::equal(player.position.z, 0); }

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Jumping::changeToNextState() {
  player.jumping = false;
  player.change_state(PlayerState::Stand);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Jumping::handle_input(const ControllerEvent &event) {}
}  // namespace senseless_soccer
