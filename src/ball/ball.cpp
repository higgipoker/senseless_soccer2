#include "ball.hpp"
#include "../metrics/metrics.hpp"
#include "ball_animations.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/widgets/sprite.hpp>

using namespace gamelib2;
namespace senseless_soccer {

/// dictated by the graphics style
const float Y_OFFSET_DUE_TO_HEIGHT = 0.5f;
const float CM_PER_PIXEL = 7.6f;

static const float GRAVITY = 9.8f; // meters per second per second
static const float AIR_FACTOR = 0.01f;
static const float co_friction = 0.99f;
static const float co_friction2 = 0.8f; // bounce fricton
static const float co_bounciness = 0.8f;
static const float ball_mass =
  200; // mass is irrelevant, used as air resistance for bounce :p
static const int SHADOW_OFFSET = 1;
static const float CAMERA_HEIGHT = Metrics::MetersToPixels(4);

// -----------------------------------------------------------------------------
// Ball
// -----------------------------------------------------------------------------
Ball::Ball(std::string in_name)
  : Entity(std::move(in_name)) {
    circle.setRadius(5.0f);
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
    position.x = 300;
    position.y = 300;
    position.z = Metrics::MetersToPixels(0);
}
// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Ball::update(float dt) {
    // ball is a special case, do not call base update

    // movement
    do_physics(dt);

    // update widget (sprite)
    if(widget.lock()){
        auto *sprite = dynamic_cast<Sprite *>(widget.lock().get());
        sprite->setPosition(position.x, position.y);
        sprite->animate();

        // sync shadow with sprite
        if (sprite->has_shadow) {
            auto *shadow = dynamic_cast<Sprite *>(sprite->shadow.lock().get());
            shadow->setPosition(sprite->position().x + SHADOW_OFFSET,
                                sprite->position().y + SHADOW_OFFSET);
            shadow->scale(sprite->scale(), sprite->scale());
        }

        perspectivize(CAMERA_HEIGHT);
    }
    circle.setPosition(position.x, position.y);
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
    if (Floats::greater_than(position.z, 0)) {
        // change gravity meters into screen pixels
        float pixels_per_sec_squared = Metrics::MetersToPixels(gravity_act);

        // find gravity in pixels for one physics frame
        float grv = pixels_per_sec_squared;

        // make the gravity vector
        Vector3 gravity(0, 0, -grv * ball_mass);

        // accumulate forces
        acceleration += gravity;
    }

    // friction
    else if (Floats::equal(velocity.z, 0) &&
             Floats::greater_than(velocity.magnidude2d(), 0)) {
        velocity *= co_friction;
    }

    // bounce
    else if (Floats::less_than(position.z, 0) &&
             Floats::less_than(velocity.z, 0)) {
        velocity.z = -velocity.z * co_bounciness;
        // round off float unlimited bounce
        float v = fabsf(velocity.z);
        if (Floats::less_than(v, 0.5f)) {
            position.z = 0;
            velocity.z = 0;
        } else {
            velocity *= co_friction2;
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
    float dimensions = circle.getRadius() * 2;
    float dist_from_camera = camera_height - position.z;
    float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
    float degs = DEGREES(angular_diameter);
    float sprite_scale_factor = degs / dimensions;

    Sprite *sprite = dynamic_cast<Sprite *>(widget.lock().get());

    float sprite_ratio = dimensions / sprite->image_width;
    sprite_scale_factor *= sprite_ratio;
    sprite->scale(sprite_scale_factor, sprite_scale_factor);

    // y offset due to height
    float z_cm = position.z * CM_PER_PIXEL;

    if (Floats::greater_than(z_cm, 0)) {
        // tmp hard code offset = 0.133px per cm
        float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
        sprite->move(0, -y_offset);
    }

    // update the shadow
}

// -----------------------------------------------------------------------------
// onMoved
// -----------------------------------------------------------------------------
void Ball::onMoved(const Vector3 &new_position, float dx, float dy) {
    position.x += dx;
    position.y += dy;
    circle.setPosition(position.x, position.y);
}

// -----------------------------------------------------------------------------
// kick
// -----------------------------------------------------------------------------
void Ball::kick(const Vector3 &force) {
    acceleration.reset();
    velocity.reset();
    acceleration = force;
}
} // namespace senseless_soccer
