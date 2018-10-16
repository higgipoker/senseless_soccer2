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
Pitch::~Pitch() = default;

// -----------------------------------------------------------------------------
// on_moved
// -----------------------------------------------------------------------------
void Pitch::onDragged(const gamelib2::Vector3 &diff) {
    Entity::onDragged(diff);
    if (widget) {
        widget->move(diff.x, diff.y);
    }
}
} // namespace senseless_soccer
