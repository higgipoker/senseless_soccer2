#include "running.hpp"
#include <gamelib2/compass/compass.hpp>
#include <gamelib2/physics/collisions.hpp>
#include "../player.hpp"
#include "standing.hpp"

using namespace gamelib2;
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Run
// -----------------------------------------------------------------------------
Running::Running(Player &context)
    : State(context, "running"), ms_between_touches(0) {}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void Running::start() {
  touch_timer.Start();
  if (player.widget) {
    player.startAnimation(Player::runmap[player.facing.direction]);
  }
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Running::update(const float dt) {
  State::update(dt);

  if (!player.ball_under_control()) {
    touch_timer.Start();
  }

  // close control
  if (player.changed_direction) {
    // change the running animation
    if (player.widget) {
      player.startAnimation(Player::runmap[player.facing.direction]);
    }

    // close control
    if (player.ball_under_control()) {
      player.do_close_control();
      touch_timer.Start();
    }
  }

  // or dribble
  else if (Collision::collides(player.feet, Player::ball->circle)) {
    if (touch_timer.GetLiveTime() >= ms_between_touches) {
      if (player.velocity.magnitude2d()) {
        player.do_dribble();
        touch_timer.Start();
      }
    }
  }
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void Running::end() {}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool Running::finished() {
  return (Floats::equal(player.velocity.magnitude2d(), 0) || player.jumping ||
          player.sliding);
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void Running::changeToNextState() {
  if (player.sliding) {
    player.change_state(PlayerState::Slide);
  } else if (player.jumping) {
    player.change_state(PlayerState::Jump);
  } else {
    player.change_state(PlayerState::Stand);
  }
}

}  // namespace senseless_soccer
