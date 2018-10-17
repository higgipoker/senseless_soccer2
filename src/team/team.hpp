#pragma once
#include "../joysticker/sensicontroller.hpp"
#include <gamelib2/game/entity.hpp>
#include <vector>

using namespace gamelib2;
namespace senseless_soccer {
enum class TeamState { Defend, Attack };
class Player;
class Team : public Entity {
public:
    Team(std::__cxx11::string in_name);

    // uodate each game frame
    void update(float dt) override;

    // add a player to the team
    void addPlayer(Player *p);

    // controller for this team
    SensiController *controller = nullptr;

    // track important players
    struct {
        Player *closest_to_ball = nullptr;
        Player *in_possession = nullptr;
        std::vector<Player *> pass_candidates;
    } key_players;

    // team has to control player in possession (only one!)
    bool requestPossession(Player *p);
    void lostPossession(Player *p);

protected:
    // players in this team
    std::vector<Player *> players;
    std::vector<Player *> subs;

    // update helpers
    void set_key_players();
    void update_controller();

public:
    friend class Player;
};

} // namespace senseless_soccer
