#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/widgets/widget.hpp>

using namespace gamelib2;
namespace senseless_soccer {

class Ball : public Entity {
public:
  // construct with an entity name
  Ball(std::string in_name, float dt = 0.01f);

  virtual ~Ball() = default;

  // main update
  void update(float dt) override;

  // the entity was manually moved
  void onDragged(const Vector3 &new_position);

  // kick it
  void kick(const Vector3 &force);

  // bounce off a barrier
  void rebound(Vector3 &wall, const Vector3 dampen = Vector3(1, 1, 1));

  // apply side spin
  void addSideSpin(const Vector3 &s);

  // apply top/back spin
  void addTopSpin(const Vector3 &s);

  // ball collidable
  sf::CircleShape circle;

  // temporary bounds
  sf::RectangleShape bounds;

  // ball environment for physics
  struct {
    float gravity = 9.8f;
    float co_air_resistance = -0.01f;
    float co_friction = -0.99f;
    float co_friction_bounce = 0.9f;
    float co_bounciness = 0.85f;
    float co_spin_decay = 0.8f;
    float ball_mass = 1.0f;
    float infinite_bounce_factor = 12.0f;
  } environment;

protected:
  // helper for ball physics
  void do_physics(float dt);

  // add perspective to the ball
  void perspectivize(float camera_height) override;

  // for verlet
  Vector3 old_velocity;

  // tmp keep in bounds
  void keep_in_bounds();

  // forces acting on the ball
  struct {
    Vector3 drag;
    Vector3 topspin;
    Vector3 sidespin;
    Vector3 gravity;
  } forces;

public:
  friend class BallFactory;
};

} // namespace senseless_soccer
