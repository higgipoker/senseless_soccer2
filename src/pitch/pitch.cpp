#include "pitch.hpp"
#include "../metrics/metrics.hpp"

#include <gamelib2/widgets/widget.hpp>

namespace senseless_soccer {

// temp
static const int grid_columns = 15;
static const int grid_rows = 19;

// -----------------------------------------------------------------------------
// Pitch
// -----------------------------------------------------------------------------
Pitch::Pitch() {
  gamelib2::Entity::create("pitch", "pitch");
  // det up a default pitch size
  dimensions.bounds.left = 250;
  dimensions.bounds.top = 250;
  dimensions.bounds.width = static_cast<float>(Metrics::MetersToPixels(69));
  dimensions.bounds.height = static_cast<float>(Metrics::MetersToPixels(105));
  dimensions.center_circle_radius = Metrics::MetersToPixels(9.15f);

  // north 6 yard
  dimensions.north_6.width =
      static_cast<float>(Metrics::MetersToPixels(18.32f));
  dimensions.north_6.height = static_cast<float>(Metrics::MetersToPixels(5.5f));
  dimensions.north_6.left = dimensions.bounds.left +
                            (dimensions.bounds.width / 2) -
                            (dimensions.north_6.width / 2);
  dimensions.north_6.top = dimensions.bounds.top;

  // north 18 yard
  dimensions.north_18.width =
      static_cast<float>(Metrics::MetersToPixels(40.32f));
  dimensions.north_18.height =
      static_cast<float>(Metrics::MetersToPixels(16.5f));
  dimensions.north_18.left =
      (dimensions.bounds.left + dimensions.bounds.width / 2) -
      (dimensions.north_18.width / 2);
  dimensions.north_18.top = dimensions.bounds.top;

  // south 6
  dimensions.south_6 = dimensions.north_6;
  dimensions.south_6.top = dimensions.bounds.top + dimensions.bounds.height -
                           dimensions.south_6.height;

  // south 18
  dimensions.south_18 = dimensions.north_18;
  dimensions.south_18.top = dimensions.bounds.top + dimensions.bounds.height -
                            dimensions.south_18.height;

  // center point
  dimensions.center.x = dimensions.bounds.left + (dimensions.bounds.width / 2);
  dimensions.center.y = dimensions.bounds.top + (dimensions.bounds.height / 2);

  // goals (for actual goal detection)
  dimensions.goal_north.left =
      dimensions.bounds.left + dimensions.bounds.width / 2 -
      static_cast<float>(Metrics::MetersToPixels(3.66f));
  dimensions.goal_north.top =
      dimensions.bounds.top - static_cast<float>(Metrics::MetersToPixels(2));
  dimensions.goal_north.width =
      static_cast<float>(Metrics::MetersToPixels(7.32f));
  dimensions.goal_north.height =
      static_cast<float>(Metrics::MetersToPixels(2));  // depth of goal

  dimensions.goal_south = dimensions.goal_north;
  dimensions.goal_south.top +=
      dimensions.bounds.height + Metrics::MetersToPixels(2);

  // goals gfx (for positiong sprites)
  goal_north_gfx.width = static_cast<float>(Metrics::MetersToPixels(7.32f));
  goal_north_gfx.height = static_cast<float>(Metrics::MetersToPixels(2.44f));
  goal_north_gfx.left = (dimensions.bounds.left + dimensions.bounds.width / 2) -
                        (goal_north_gfx.width / 2) + 76;
  goal_north_gfx.top = dimensions.bounds.top;

  goal_south_gfx = goal_north_gfx;
  goal_south_gfx.top += dimensions.bounds.height;

  grid.init(static_cast<int>(dimensions.bounds.left),
            static_cast<int>(dimensions.bounds.top),
            static_cast<int>(dimensions.bounds.width),
            static_cast<int>(dimensions.bounds.height), grid_columns,
            grid_rows);
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
}  // namespace senseless_soccer
