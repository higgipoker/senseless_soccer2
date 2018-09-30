#include "ball.hpp"
#include "../metrics/metrics.hpp"
#include "ball_animations.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/widgets/sprite.hpp>

namespace senseless_soccer {

/// dictated by the graphics style
const float Y_OFFSET_DUE_TO_HEIGHT = 0.5f;
const float CM_PER_PIXEL = 7.6f;

static const float GRAVITY = 9.8f; // meters per second per second
static const float AIR_FACTOR = 0.01f;
static const float co_friction = 0.1f;
static const float co_bounciness = 0.8f;
static const float ball_mass =
  100; // mass is irrelevant, used as air resistance for bounce :p
static const int SHADOW_OFFSET = 1;

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
// activate
// -----------------------------------------------------------------------------
void Ball::activate() {
    position.x = 100;
    position.y = 100;
    position.z = 10;
    perspectivize(40);
}
// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Ball::update(float dt) {
    // ball is a special case, do not call base update

    // movement
    do_physics(dt);

    // update widget (sprite)
    auto w = widget.lock();
    gamelib2::Sprite *sprite = static_cast<gamelib2::Sprite *>(w.get());
    sprite->setPosition(position.x, position.y);
    sprite->animate();

    // sync shadow with sprite
    if (sprite->has_shadow) {
        auto s = widget.lock();
        auto *shadow =
          static_cast<gamelib2::Sprite *>(sprite->shadow.lock().get());
        shadow->setPosition(sprite->position().x + SHADOW_OFFSET,
                            sprite->position().y + SHADOW_OFFSET);
        shadow->scale(sprite->scale(), sprite->scale());
    }

    perspectivize(10);
}

// -----------------------------------------------------------------------------
// do_physics
// -----------------------------------------------------------------------------
void Ball::do_physics(float dt) {
    // formulas are in seconds, physics step is in "dt"
    float time_slice = dt / 1;

    // actual acceleration due to gravity for this time slice
    float gravity_act = GRAVITY * time_slice;

    // gravity
    if (gamelib2::Floats::greater_than(position.z, 0)) {
        // change gravity meters into screen pixels
        float pixels_per_sec_squared = Metrics::MetersToPixels(gravity_act);

        // find gravity in pixels for one physics frame
        float grv = pixels_per_sec_squared;

        // make the gravity vector
        gamelib2::Vector3 gravity(0, 0, -grv * ball_mass);

        // accumulate forces
        acceleration += gravity;
    }

    // friction
    else if (gamelib2::Floats::less_than(velocity.z, 0) &&
             gamelib2::Floats::greater_than(velocity.magnidude2d(), 0)) {
        velocity *= co_friction;
    }

    // bounce
    else if (gamelib2::Floats::less_than(position.z, 0) &&
             gamelib2::Floats::less_than(velocity.z, 0)) {
        velocity.z = -velocity.z * co_bounciness;
        // round off float unlimited bounce
        float v = fabsf(velocity.z);
        if (gamelib2::Floats::less_than(v, 0.5f)) {
            position.z = 0;
            velocity.z = 0;
        }
    }

    // basic euler is enough for our purposes
    velocity += acceleration * dt;
    position += velocity * dt;

    // reset acceleration ready for next frame
    acceleration.reset();
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void Ball::perspectivize(float camera_height) {
    // size depending on distance from camera
    float dimensions = radius * 2;
    float dist_from_camera = camera_height - position.z;
    float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
    float degs = DEGREES(angular_diameter);
    float sprite_scale_factor = degs / dimensions;

    gamelib2::Sprite *sprite =
      static_cast<gamelib2::Sprite *>(widget.lock().get());

    float sprite_ratio = dimensions / sprite->image_width;
    sprite_scale_factor *= sprite_ratio;
    sprite->scale(sprite_scale_factor, sprite_scale_factor);

    // y offset due to height
    float z_cm = position.z * CM_PER_PIXEL;

    if (gamelib2::Floats::greater_than(z_cm, 0)) {
        // tmp hard code offset = 0.133px per cm
        float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
        sprite->move(0, -y_offset);
    }

    // update the shadow
}

// -----------------------------------------------------------------------------
// onMoved
// -----------------------------------------------------------------------------
void Ball::onMoved(const gamelib2::Vector3 &new_position, float dx, float dy) {
    position.x += dx;
    position.y += dy;
    perspectivize(10);
}
} // namespace senseless_soccer
