#include "team.hpp"
#include "../player/player.hpp"

namespace senseless_soccer {

// -----------------------------------------------------------------------------
// sort predicate for players
// -----------------------------------------------------------------------------
struct {
    bool operator()(const Player *p1, const Player *p2) const {
        return p1->distance_from_ball < p2->distance_from_ball;
    }
} sort_players;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Team::Team(std::string in_name)
  : Entity(std::move(in_name)) {
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::update(float dt) {
    set_key_players();
    update_controller();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::addPlayer(Player *p) {
    players.emplace_back(p);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::set_key_players() {
    std::sort(players.begin(), players.end(), sort_players);
    key_players.closest_to_ball = players[0];
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::update_controller() {
    if (controller) {
        controller->attachToPlayer(key_players.closest_to_ball);
    }
}
} // namespace senseless_soccer
