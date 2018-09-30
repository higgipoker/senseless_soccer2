#pragma once
#include <gamelib2/game/entity.hpp>
namespace senseless_soccer {

class Pitch : public gamelib2::Entity {
public:
    // construct with an entity name
    Pitch(std::string in_name);
    virtual ~Pitch();

    // the entity was manually moved
    void onMoved(const gamelib2::Vector3 &new_position, float dx = 0,
                 float dy = 0) override;

protected:

};

} // namespace senseless_soccer
