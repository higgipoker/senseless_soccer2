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
Team::Team(const std::string in_name)
  : Entity(in_name) {
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Team::~Team() {
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::update(float dt) {
    std::sort(players.begin(), players.end(), sort_players);
    closest_to_ball = players.at(0);

    if (controller) {
        controller->attachToPlayer(closest_to_ball);
    }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::addPlayer(Player *p) {
    players.emplace_back(p);
}

} // namespace senseless_soccer
