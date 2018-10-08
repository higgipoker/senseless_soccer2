#include "ball.hpp"
#include "../metrics/metrics.hpp"
#include "ball_animations.hpp"
#include "../joysticker/aftertouch.hpp"

#include <gamelib2/math/vector.hpp>
#include <gamelib2/widgets/sprite.hpp>

#include <iostream>
#include <cassert>

using namespace gamelib2;
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// stuff for ball physics mark 2!!!
// -----------------------------------------------------------------------------

// Vector initial_force;
// Vector topspin;
// Vector sidespin;
// Vector drag;
// float air_density;
// float ball_mass;

// -----------------------------------------------------------------------------

/// dictated by the graphics style
const float Y_OFFSET_DUE_TO_HEIGHT = 0.5f;
const float CM_PER_PIXEL = 7.6f;

static const float GRAVITY = 9.8f; // meters per second per second
static const float AIR_FACTOR = 0.01f;
static const float co_friction = 0.98f;
static const float co_friction_bounce = 0.9f; // bounce fricton
static const float co_bounciness = 0.8f;
static const float co_spin_decay = 0.001f; // how much spin decays over time
static const float ball_mass = 200.f; // used in air resistance calc
static const int SHADOW_OFFSET = 1;
static const float CAMERA_HEIGHT = Metrics::MetersToPixels(4);

using std::cout;
using std::endl;

// -----------------------------------------------------------------------------
// Ball
// -----------------------------------------------------------------------------
Ball::Ball(std::string in_name, float dt)
  : Entity(std::move(in_name)) {
    circle.setRadius(4.0f);

    // gravity is a constant, can set it up here once

    // formulas are in seconds, physics step is in "dt"
    float time_slice = dt / 1;

    // actual acceleration due to gravity for this time slice
    float gravity_act = GRAVITY * time_slice;

    // change gravity meters into screen pixels
    float pixels_per_sec_squared = Metrics::MetersToPixels(gravity_act);

    // find gravity in pixels for one physics frame
    float grv = pixels_per_sec_squared;

    // make the gravity vector
    forces.gravity = Vector3(0, 0, -grv * ball_mass);
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
    position.x = 60;
    position.y = 60;
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
    if (widget) {
        Sprite *sprite = static_cast<Sprite *>(widget);
        sprite->setPosition(position.x, position.y);
        sprite->animate();

        // sync shadow with sprite
        Sprite *shadow = sprite->getShadow();
        if (shadow) {
            shadow->setPosition(sprite->position().x + SHADOW_OFFSET,
                                sprite->position().y + SHADOW_OFFSET);
            shadow->scale(sprite->scale(), sprite->scale());
        }

	// add perspective to the ball sprite
        perspectivize(CAMERA_HEIGHT);
    }
    circle.setPosition(position.x, position.y);
}

// -----------------------------------------------------------------------------
// do_physics
// -----------------------------------------------------------------------------
void Ball::do_physics(float dt) {

    // save bounce so we dont have to calc again for dampening
    bool bounced = false;

    // ball is in the air so do gravity, drag and spin
    if (Floats::greater_than(position.z, 0)) {

        //
        // gravity
        //
        acceleration += forces.gravity;

        //
        // drag
        //
        // drag increases with height and ball size
        forces.drag = Vector3(velocity.reverse() * AIR_FACTOR * position.z *
                              circle.getRadius() * 2);
        acceleration += forces.drag;

        //
        // spin
        //
        acceleration += forces.topspin;
        acceleration += forces.sidespin;
    }

    // friction
    else if (Floats::equal(velocity.z, 0) &&
             Floats::greater_than(velocity.magnidude2d(), 0)) {
        velocity *= co_friction;
    }

    // bounce if z < - and moving down
    else if (Floats::less_than(position.z, 0) &&
             Floats::less_than(velocity.z, 0)) {

        // do dampening for infinite bounce later
        bounced = true;

        // apply bounciness
        velocity.z = -velocity.z * co_bounciness;

        // ball also loses some speed on bounce
        velocity *= co_friction_bounce;
    }

    // -------------------------------------------------------------------------
    // MOTION INTEGRATION
    // pick one, these 2 are very similar!

    // 1. verlet motion integration
    old_velocity = velocity;
    velocity = velocity + acceleration * dt;
    position = position + (old_velocity + velocity) * 0.5 * dt;

    // 2. semi-implicit euler motion integration
    //    velocity += acceleration * dt;
    //    position += velocity * dt;

    //
    // -------------------------------------------------------------------------

    // round off infinite bounce
    if (bounced) {
        if (Floats::less_than(fabsf(velocity.z), 20.f)) {
            position.z = 0;
            velocity.z = 0;
        }
    }

    // spin decays over time
    if (Floats::greater_than(forces.topspin.magnidude2d(), 0)) {
        forces.topspin = forces.topspin * co_spin_decay;
    } else {
        forces.topspin.reset();
    }
    if (Floats::greater_than(forces.sidespin.magnidude2d(), 0)) {
        forces.sidespin = forces.sidespin * co_spin_decay;
    } else {
        forces.sidespin.reset();
    }

    // reset acceleration ready for next frame
    acceleration.reset();

    if (forces.sidespin.magnitude()) {
        cout << forces.sidespin.magnitude() << endl;
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

    assert(widget);
    Sprite *sprite = static_cast<Sprite *>(widget);

    float sprite_ratio = dimensions / sprite->image_width;
    sprite_scale_factor *= sprite_ratio;
    sprite->scale(sprite_scale_factor, sprite_scale_factor);

    // y offset due to height
    float z_cm = position.z * CM_PER_PIXEL;

    if (Floats::greater_than(z_cm, 0)) {
        // tmp hard code offset = 0.133px per cm according to sprite design
        float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
        sprite->move(0, -y_offset);
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
// kick
// -----------------------------------------------------------------------------
void Ball::kick(const Vector3 &force) {
    acceleration.reset();
    velocity.reset();
    acceleration = force;
}

// -----------------------------------------------------------------------------
// addSideSpin
// -----------------------------------------------------------------------------
void Ball::addSideSpin(const Vector3 &s) {
    forces.sidespin += s;
}

// -----------------------------------------------------------------------------
// addTopSpin
// -----------------------------------------------------------------------------
void Ball::addTopSpin(const Vector3 &s) {
    forces.topspin += s;
}

// -----------------------------------------------------------------------------
// aftertouch
// -----------------------------------------------------------------------------
void Ball::aftertouch(const Vector3 &aftertouch) {
    acceleration += aftertouch;
}
} // namespace senseless_soccer
