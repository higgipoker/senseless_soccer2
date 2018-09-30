#include "ball.hpp"
#include "ball_animations.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Ball
// -----------------------------------------------------------------------------
Ball::Ball(std::string in_name)
  : gamelib2::Entity(std::move(in_name)) {
}

// -----------------------------------------------------------------------------
// ~Ball
// -----------------------------------------------------------------------------
Ball::~Ball() {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Ball::update(float dt) {
    // has the sprite been manually moved
    auto w = widget.lock();
    gamelib2::Vector3 widget_position(w->position().x, w->position().y);
    if (!widget_position.equals(position)) {
        position.x = w->position().x;
        position.y = w->position().y;
    }
    // update widget (sprite)
    w->setPosition(position.x, position.y);
    w->animate();
}

} // namespace senseless_soccer
