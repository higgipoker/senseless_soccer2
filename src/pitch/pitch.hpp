#pragma once
#include <gamelib2/game/entity.hpp>
namespace senseless_soccer {

class Pitch : public gamelib2::Entity {
public:
    // construct with an entity name
    Pitch(std::string in_name);
    virtual ~Pitch();

    // the entity was manually moved
    void onDragged(const gamelib2::Vector3 &new_position) override;

protected:
};

} // namespace senseless_soccer
