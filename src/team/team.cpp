#include "team.hpp"
#include "../player/player.hpp"

namespace senseless_soccer {
namespace team {
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
    : Entity("team", std::move(in_name)), enter_pitch(*this) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::init() { current_state.start(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::update(float dt) {
  set_key_players();
  update_controller();
  current_state.update(dt);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::addPlayer(Player *p) {

  // add player to team
  players.emplace_back(p);

  // tell player of team
  p->setTeam(this);

  // apply the kit to player
  dynamic_cast<gamelib2::Sprite *>(p->widget.get())->swapColors(kit1.palette);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::set_key_players() {
  if (players.empty())
    return;
  std::sort(players.begin(), players.end(), sort_players);
  size_t i = 0;
  do {
    key_players.closest_to_ball = players[i++];
  } while (key_players.closest_to_ball->in_possession &&
           i < players.size() - 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::update_controller() {
  if (controller == nullptr)
    return;
  if (players.empty())
    return;

  Player *player = nullptr;

  // attach to closest to ball, or player in possession
  if (key_players.in_possession) {
    player = key_players.in_possession;
  } else if (key_players.closest_to_ball) {
    player = key_players.closest_to_ball;
  }

  if (player != controller->player) {
    controller->attachToPlayer(player);
  }
}

// -----------------------------------------------------------------------------
// request_possession
// -----------------------------------------------------------------------------
bool Team::requestPossession(Player *p) {
  if (key_players.in_possession) {
    return false;
  }
  key_players.in_possession = p;
  return true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Team::lostPossession(Player *p) {
  if (key_players.in_possession == p) {
    key_players.in_possession = nullptr;
  }
}
} // namespace team
} // namespace senseless_soccer
