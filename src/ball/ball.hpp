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
    void onMoved(const Vector3 &new_position, float dx = 0,
                 float dy = 0) override;

    // kick it
    void kick(const Vector3 &force);

    // aftertouch interface
    void aftertouch(const Vector3 &aftertouch);

    // ball collidable
    sf::CircleShape circle;

protected:
    // helper for ball physics
    void do_physics(float dt);

    // add perspective to the ball
    void perspectivize(float camera_height) override;

    // construct with an entity name
    Ball(std::string in_name);
    virtual ~Ball();

    Vector3 old_position; // for verlet
    Vector3 old_velocity;

public:
    friend class BallFactory;
};

} // namespace senseless_soccer
