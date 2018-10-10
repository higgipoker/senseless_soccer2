#pragma once
#include "../joysticker/sensicontroller.hpp"
#include <gamelib2/game/entity.hpp>
#include <vector>

using namespace gamelib2;
namespace senseless_soccer {

enum class TeamState { Defend, Attack };

class Player;

// todo make entity?
class Team : public Entity {
public:
    Team(const std::string in_name);
    ~Team() override;
    void update(float dt) override;
    void addPlayer(Player *p);

    Player *closest_to_ball = nullptr;
    SensiController *controller = nullptr;

private:
    std::vector<Player *> players;
};

} // namespace senseless_soccer
