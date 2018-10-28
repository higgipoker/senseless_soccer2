#pragma once
#include <SFML/Graphics.hpp>
#include <gamelib2/game/entity.hpp>
namespace senseless_soccer {

typedef struct {

  // pitch lines
  sf::FloatRect bounds;
  sf::FloatRect north_6;
  sf::FloatRect north_18;
  sf::FloatRect south_6;
  sf::FloatRect south_18;
  sf::FloatRect center;
  int center_circle_radius;

  // goals
  sf::FloatRect goal_north;
  sf::FloatRect goal_south;

} PitchDimensions;

class Pitch : public gamelib2::Entity {
public:
  // construct with an entity name
  Pitch();
  virtual ~Pitch();

  // the entity was manually moved
  void onDragged(const gamelib2::Vector3 &new_position) override;

  PitchDimensions dimensions;
  // goals graphical
  sf::FloatRect goal_north_gfx;
  sf::FloatRect goal_south_gfx;

protected:
};

} // namespace senseless_soccer
