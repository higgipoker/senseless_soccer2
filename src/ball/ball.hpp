#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <gamelib2/game/entity.hpp>

using namespace gamelib2;
namespace senseless_soccer {

class Ball : public Entity {
public:
    // main update
    void update(float dt) override;

    // activate when sprite is connected
    void activate() override;

    // the entity was manually moved
    void onDragged(const Vector3 &new_position);

    // kick it
    void kick(const Vector3 &force);

    // aftertouch interface
    void aftertouch(const Vector3 &aftertouch);

    // apply spin to the ball
    void addSideSpin(const Vector3 &s);
    void addTopSpin(const Vector3 &s);

    // ball collidable
    sf::CircleShape circle;

protected:
    // helper for ball physics
    void do_physics(float dt);

    // add perspective to the ball
    void perspectivize(float camera_height) override;

    // forces acting on the ball
    struct {
        Vector3 drag;
        Vector3 topspin;
        Vector3 sidespin;
        Vector3 gravity;
    } forces;

    // construct with an entity name
    Ball(std::string in_name, float dt = 0.01f);
    virtual ~Ball() override;

    Vector3 old_velocity; // for verlet

public:
    friend class BallFactory;
};

} // namespace senseless_soccer
