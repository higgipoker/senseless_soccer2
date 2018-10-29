#pragma once
#include "../joysticker/sensicontroller.hpp"
#include "enterpitch.hpp"
#include "kit.hpp"
#include <gamelib2/game/entity.hpp>
#include <vector>

using namespace gamelib2;
namespace senseless_soccer {
class Player;
namespace team {
enum class TeamState { Defend, Attack };
class Team : public Entity {
public:
  Team(std::string in_name);

  // init
  void init();

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

  // attacking goal
  sf::FloatRect attacking_goal;

  // defending goal
  sf::FloatRect defending_goal;

  // team has to control player in possession (only one!)
  bool requestPossession(Player *p);
  void lostPossession(Player *p);

  Kit kit1;
  Kit kit12;
  Kit kit3;

protected:
  // players in this team
  std::vector<Player *> players;
  std::vector<Player *> subs;

  EnterPitch enter_pitch;
  State &current_state = enter_pitch;

  // update helpers
  void set_key_players();
  void update_controller();

public:
  friend class senseless_soccer::Player;
  friend class State;
  friend class EnterPitch;
};
} // namespace team
} // namespace senseless_soccer
