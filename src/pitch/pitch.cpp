#include "pitch.hpp"

#include <gamelib2/widgets/widget.hpp>
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Pitch
// -----------------------------------------------------------------------------
Pitch::Pitch(std::string in_name)
  : gamelib2::Entity(std::move(in_name)) {
}

// -----------------------------------------------------------------------------
// ~Ball
// -----------------------------------------------------------------------------
Pitch::~Pitch() {
}

// -----------------------------------------------------------------------------
// on_moved
// -----------------------------------------------------------------------------
void Pitch::onMoved(const gamelib2::Vector3 &new_position, float dx, float dy) {
    Entity::onMoved(new_position);
    if (widget) {
        widget->setPosition(position.x, position.y);
    }
}
} // namespace senseless_soccer
