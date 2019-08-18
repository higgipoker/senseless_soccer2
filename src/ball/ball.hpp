#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/widgets/widget.hpp>

using namespace gamelib2;
namespace senseless_soccer {

class Ball : public Entity {
 public:
  /**
   * @brief Ball
   * @param in_name
   * @param dt
   */
  Ball(const std::string &in_name);

  /**
   */
  virtual ~Ball() = default;

  /**
   * @brief update
   * @param dt
   */
  void step(float dt) override;

  /**
   * @brief onDragged
   * @param new_position
   */
  void onDragged(const Vector3 &new_position) override;

  /**
   * @brief apply_force
   * @param force
   */
  void applyForce(const Vector3 &force);

  /**
   * @brief stop
   */
  void stop();

  /**
   * @brief rebound
   * @param wall
   * @param dampen
   */
  void rebound(Vector3 &wall, const Vector3 dampen = Vector3(1, 1, 1));

  /**
   * @brief addSideSpin
   * @param s
   */
  void addSideSpin(const Vector3 &s);

  /**
   * @brief addTopSpin
   * @param s
   */
  void addTopSpin(const Vector3 &s);

  // ball collidable
  sf::CircleShape circle;

  // temporary bounds
  sf::RectangleShape bounds;

  // ball environment for physics
  struct {
    float gravity = 9.8f;
    float air_density = 1.0f;
    float co_drag = 0.9f;
    float co_friction = 0.01f;
    float co_friction_bounce = 0.9f;
    float co_bounciness = 0.9f;
    float co_spin_decay = 0.8f;
  } environment;

  // forces acting on the ball
  struct {
    Vector3 drag;
    Vector3 topspin;
    Vector3 sidespin;
    Vector3 friction;
    Vector3 gravity{0, 0, 9.8f};

    /**
     * @brief reset
     */
    void reset() {
      drag.reset();
      topspin.reset();
      sidespin.reset();
      friction.reset();
    }
  } forces;

 protected:
  /**
   * @brief do_physics
   * @param dt
   */
  void update_position(float dt);

  /**
   * @brief integrate_euler
   * @param _dt
   */
  void euler_integration(float _dt);

  /**
   * @brief integrate_improved_euler
   * @param _dt
   */
  void improved_euler_integration(float _dt);

  /**
   * @brief apply_gravity
   * @param dt
   */
  void apply_gravity(float dt);

  /**
   * @brief apply_friction
   */
  void apply_friction();

  /**
   * @brief apply_spin
   */
  void apply_spin();

  /**
   * @brief decay_spin
   */
  void decay_spin();

  /**
   * @brief apply_drag
   */
  void apply_drag(float dt);

  /**
   * @brief clamp_to_ground
   */
  void clamp_to_ground(void);

  /**
   * @brief collide_ground
   * @return
   */
  bool collide_ground(void);

  /**
   * @brief bounce
   */
  void bounce();

  /**
   * @brief in_air
   * @return
   */
  inline bool in_air() { return Floats::greater_than(position.z, 0); }

  /**
   * @brief update_sprite
   */
  void update_sprite();

  /**
   * @brief perspectivize
   * @param camera_height
   */
  void perspectivize(float camera_height) override;

  // for verlet
  Vector3 old_velocity;

  /**
   * @brief keep_in_bounds
   */
  void keep_in_bounds();

 public:
  friend class BallFactory;
};

}  // namespace senseless_soccer
