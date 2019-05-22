#pragma once

#include <gamelib2/game/entity.hpp>
#include <gamelib2/math/vector.hpp>
#include <gamelib2/utils/grid.hpp>

#include <SFML/Graphics.hpp>

#include <memory>

namespace senseless_soccer {

typedef struct {
  // pitch lines
  sf::FloatRect bounds;
  sf::FloatRect north_6;
  sf::FloatRect north_18;
  sf::FloatRect south_6;
  sf::FloatRect south_18;
  int center_circle_radius;

  // goals
  sf::FloatRect goal_north;
  sf::FloatRect goal_south;

  // points of interest
  gamelib2::Vector3 center;

} PitchDimensions;

class Pitch : public gamelib2::Entity {
 public:
  Pitch();
  virtual ~Pitch();

  // the entity was manually moved
  void onDragged(const gamelib2::Vector3 &new_position) override;

  // dimensions
  PitchDimensions dimensions;

  // goals graphical
  sf::FloatRect goal_north_gfx;
  sf::FloatRect goal_south_gfx;

  //  a pitch has an underlying grid system for tactics
  gamelib2::Grid grid;

 protected:
};

}  // namespace senseless_soccer
