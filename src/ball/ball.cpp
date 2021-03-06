#include "ball.hpp"

#include "../joysticker/aftertouch.hpp"
#include "../metrics/metrics.hpp"
#include "ball_animations.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include <cassert>
#include <iostream>

using namespace gamelib2;
namespace senseless_soccer {

const int SHADOW_OFFSET = 1;
const float CLAMP_INF_BOUNCE = 0.01f;

// -----------------------------------------------------------------------------
// Ball
// -----------------------------------------------------------------------------
Ball::Ball(const std::string &in_name) {
  create("ball", in_name);
  circle.setRadius(5.0f);

  // to not have to change the header file while tweaking
  environment.gravity = 9.8f;
  environment.air_density = 1.0f;
  environment.co_drag = 0.01f;
  environment.co_friction = 0.01f;
  environment.co_friction_bounce = 0.1f;
  environment.co_bounciness = 0.8f;
  environment.co_spin_decay = 0.8f;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Ball::step(float dt) {
  // ball is a special case, do not call base update

  // physics simulation
  update_position(dt);

  // sprite animation
  animate(dt);

  // special ball sprite stuff
  update_sprite();
}

// -----------------------------------------------------------------------------
// do_physics
// -----------------------------------------------------------------------------
void Ball::update_position(float dt) {
  // either bounce or integrate
  if (collide_ground()) {
    bounce();
  } else {
    // either gravity or friction
    if (in_air()) {
      apply_gravity(dt);
      apply_drag(dt);
    } else {
      apply_friction();
    }
    apply_spin();
    decay_spin();
    // euler_integration(dt);
    improved_euler_integration(dt);
  }

  // the shape for collisions
  circle.setPosition(position.x, position.y);

  force.reset();
  forces.reset();
  return;
}

// -----------------------------------------------------------------------------
// euler_integration
// -----------------------------------------------------------------------------
void Ball::euler_integration(float dt) {
  // drag
  force = (force - (velocity.multiply(forces.friction)));

  // acceleration = force / mass
  acceleration = force / mass;

  // difference in velocity = acceleration * difference time
  Vector3 dv = acceleration * dt;

  // velocity = velocity + difference in velocity
  velocity += dv;

  // difference in position = velocity * difference time
  Vector3 dp = velocity * dt;

  // convert to pixels
  dp = Metrics::MetersToPixels(dp);

  // update position
  position += dp;
}

// -----------------------------------------------------------------------------
// improved_euler_integration
// -----------------------------------------------------------------------------
void Ball::improved_euler_integration(float dt) {
  // step 1
  force = (force - (velocity.multiply(forces.friction)));
  acceleration = force / mass;
  Vector3 k1 = acceleration * dt;

  // step 2
  force = (force - (velocity + k1).multiply(forces.friction));
  acceleration = force / mass;
  Vector3 k2 = acceleration * dt;

  // step 3
  force = (force - (velocity + k1 + k2).multiply(forces.friction));
  acceleration = force / mass;
  Vector3 k3 = acceleration * dt;

  // update velocity
  velocity = velocity + (k1 + k2 + k3) / 3;

  // change in position (converted to pixels)
  Vector3 dp = Metrics::MetersToPixels(velocity * dt);

  // apply new position
  position = position + dp;
}

// -----------------------------------------------------------------------------
// applyForce
// -----------------------------------------------------------------------------
void Ball::applyForce(const Vector3 &_force) { force += _force; }

// -----------------------------------------------------------------------------
// apply_gravity
// -----------------------------------------------------------------------------
void Ball::apply_gravity(float dt) {
  forces.gravity.z = -environment.gravity;
  force += forces.gravity * mass * dt;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::apply_friction() {
  forces.friction.x = environment.co_friction;
  forces.friction.y = environment.co_friction;
  forces.friction.z = 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::apply_spin() {
  force += forces.sidespin;
  force += forces.topspin;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::decay_spin() {
  if (Floats::greater_than(forces.topspin.magnitude(), 0)) {
    forces.topspin = forces.topspin * environment.co_spin_decay;
  } else {
    forces.topspin.reset();
  }
  if (Floats::greater_than(forces.sidespin.magnitude(), 0)) {
    forces.sidespin = forces.sidespin * environment.co_spin_decay;
  } else {
    forces.sidespin.reset();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::apply_drag(float dt) {
  // drag = (air density * co_drag * cross section area) / 2
  // in the opposite direction to velocity
  Vector3 dir = velocity.reverse().normalise();
  forces.drag = dir * (environment.co_drag *
                       (PI * circle.getRadius() * circle.getRadius()) / 2);
  force += forces.drag * dt;
}

// -----------------------------------------------------------------------------
// clamp_to_ground
// -----------------------------------------------------------------------------
void Ball::clamp_to_ground() {
  if (Floats::less_than(position.z, 0)) {
    position.z = 0;
    velocity.z = 0;
    acceleration.z = 0;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Ball::collide_ground() {
  // moving down
  if (Floats::less_than(velocity.z, 0)) {
    // touched ground
    if (Floats::less_than(position.z, 0)) {
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::bounce() {
  position.z = 0;
  if (Floats::abs_less_than(velocity.z, CLAMP_INF_BOUNCE)) {
    velocity.z = 0;
  } else {
    velocity.z = -velocity.z;
    velocity.z *= environment.co_bounciness;
  }
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void Ball::perspectivize(float camera_height) {
  // size depending on distance from camera
  float dimensions = circle.getRadius() * 2;
  float dist_from_camera = camera_height - position.z;
  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / dimensions;

  if (auto sprite = static_cast<Sprite *>(widget)) {
    float sprite_ratio = dimensions / sprite->image_width;
    sprite_scale_factor *= sprite_ratio;
    sprite->scale(sprite_scale_factor, sprite_scale_factor);

    // y offset due to height
    float z_cm = position.z * CM_PER_PIXEL;

    if (Floats::greater_than(z_cm, 0)) {
      float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
      sprite->move(0, -y_offset);
    }
  }
}

// -----------------------------------------------------------------------------
// onMoved
// -----------------------------------------------------------------------------
void Ball::onDragged(const Vector3 &new_position) {
  position += new_position;
  circle.setPosition(position.x, position.y);
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void Ball::stop() {
  forces.sidespin.reset();
  forces.topspin.reset();
  velocity.reset();
}

// -----------------------------------------------------------------------------
// addSideSpin
// -----------------------------------------------------------------------------
void Ball::addSideSpin(const Vector3 &s) { forces.sidespin += s; }

// -----------------------------------------------------------------------------
// addTopSpin
// -----------------------------------------------------------------------------
void Ball::addTopSpin(const Vector3 &s) { forces.topspin += s; }

// -----------------------------------------------------------------------------
// rebound
// -----------------------------------------------------------------------------
void Ball::rebound(Vector3 &wall, const Vector3 dampen) {
  wall = wall.normalise();
  velocity *= dampen;
  velocity = velocity.reflect(wall);
  position += velocity * 0.01f;  // tmp fixes sticky walls
}

// -----------------------------------------------------------------------------
// keep_in_bounds
// -----------------------------------------------------------------------------
void Ball::keep_in_bounds() {
  Vector3 damp(0.8f, 0.8f, 0.0f);
  if (position.x - circle.getRadius() < bounds.getPosition().x) {
    Vector3 wall(1, 0);
    rebound(wall, damp);
  } else if (position.x + circle.getRadius() >
             bounds.getPosition().x + bounds.getSize().x) {
    Vector3 wall(1, 0);
    rebound(wall, damp);

  } else if (position.y - circle.getRadius() < bounds.getPosition().y) {
    Vector3 wall(0, 1);
    rebound(wall, damp);

  } else if (position.y + circle.getRadius() >
             bounds.getPosition().y + bounds.getSize().y) {
    Vector3 wall(0, 1);
    rebound(wall, damp);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Ball::update_sprite() {
  // update widget (sprite)
  if (auto sprite = static_cast<Sprite *>(widget)) {
    sprite->setPosition(position.x, position.y);
    perspectivize(CAMERA_HEIGHT);
  }
}

}  // namespace senseless_soccer
