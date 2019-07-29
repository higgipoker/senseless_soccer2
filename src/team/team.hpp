#pragma once

#include "defend.hpp"
#include "enterpitch.hpp"
#include "idle.hpp"
#include "kit.hpp"
#include "lineup.hpp"
#include "tactics/formation.hpp"

#include "../joysticker/sensicontroller.hpp"
#include "../match/match.hpp"
#include "../pitch/pitch.hpp"
#include "../player/ai/defend/cover.hpp"

#include <gamelib2/compass/compass.hpp>
#include <gamelib2/game/entity.hpp>

#include <vector>

using namespace gamelib2;

namespace senseless_soccer {

class Player;

namespace team {

enum class TeamState { EnterPitch, LineUp, Defend, Attack };

class Team : public Entity, public match::MatchObserver {
 public:
  Team(std::string in_name);

  // init
  void init(Pitch *p, const Direction s);

  // uodate each game frame
  void update(float dt) override;

  // add a player to the team
  void addPlayer(Player *p);

  // controller for this team
  SensiController *controller = nullptr;

  // players in this team
  std::vector<Player *> players;
  std::vector<Player *> subs;

  // track important players
  struct {
    Player *closest_to_ball = nullptr;
    Player *in_possession = nullptr;
    std::vector<Player *> pass_candidates;
  } key_players;

  // attacking goal
  sf::FloatRect attacking_goal;

  // defending goal
  sf::FloatRect defending_goal;

  // team has to control player in possession (only one!)
  bool requestPossession(Player *p);
  void lostPossession(Player *p);

  // associate aptich
  void connectPitch(Pitch *p);

  // kit
  Kit kit;

  // a formation
  std::set<std::string> formation = Formation::four_four_two;

  // side of the pitch team is defending
  Compass side = Direction::SOUTH;

  // from match observer interface
  void matchStateChanged(match::MatchState new_state);

 protected:
  // team needs to know about the pitch
  Pitch *pitch=nullptr;

  // states
  EnterPitch enter_pitch;
  LineUp lineup;
  Defend defend;
  Idle idle;
  State *current_state = &idle;
  void change_state();

  // update helpers
  void set_key_players();
  void update_controller();

 public:
  friend class senseless_soccer::Player;
  friend class senseless_soccer::ai::Cover;
  friend class State;
  friend class EnterPitch;
  friend class LineUp;
  friend class Defend;
  friend class Idle;
};
}  // namespace team
}  // namespace senseless_soccer
