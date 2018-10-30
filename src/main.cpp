#include "debug/diagnostics.hpp"
#include "match/match.hpp"
#include "memory/ballfactory.hpp"
#include "memory/playerfactory.hpp"
#include "pitch/pitch.hpp"
#include "pitch/pitchwidget.hpp"
#include "team/kit.hpp"
#include "team/team.hpp"

#include <gamelib2/engine/engine.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/input/keyboard.hpp>
#include <gamelib2/input/xbox_gamepad.hpp>
#include <gamelib2/utils/files.hpp>
#include <gamelib2/viewer/viewer.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <memory>
#include <sstream>

using namespace gamelib2;
using namespace senseless_soccer;
using namespace match;

int main() {

  // main game objects
  std::shared_ptr< Viewer > viewer = std::make_shared< Viewer >();
  std::shared_ptr< Engine > engine = std::make_shared< Engine >();
  Match match;
  Pitch pitch;
  team::Team team1("team1");
  team::Team team2("team2");

  team1.kit1 = team::Kit::make_standard_blue_kit();
  team2.kit1 = team::Kit::make_standard_red_kit();

  match.init(&team1, &team2);

  // a debug hud
  senseless_soccer::Diagnostic debug(viewer);
  viewer.get()->connectDiagnostics(debug);

  // inits static stuff
  Player::init();

  // set up a controller from a keyboard inpout
  XboxController xbox_controller;
  Keyboard keyboard;
  SensiController controller(keyboard);
  team1.controller = &controller;

  // scrolling background
  std::shared_ptr< PitchWidget > pitch_widget = std::make_shared< PitchWidget >(
    Files::getWorkingDirectory() + "/gfx/grass_horizontal.png", engine->camera);
  pitch_widget->z_order = -10;
  pitch_widget->connectEntity(&pitch);
  pitch.connectWidget(std::move(pitch_widget));
  viewer.get()->addWidget(pitch.widget);

  // auto pitch = dynamic_cast<Pitch *>(pitch_entity);
  team2.attacking_goal = pitch.dimensions.goal_north;
  team2.defending_goal = pitch.dimensions.goal_south;

  // test
  pitch.widget->addChild(controller.label);

  // players
  std::vector< std::unique_ptr< Player > > players;

  // team 1
  for (int i = 0; i < 1; ++i) {
    std::stringstream name;
    name << "player" << i;
    auto player = PlayerFactory::makePlayer(name.str());
    player->setPosition(300, 300);
    auto *sprite = dynamic_cast< Sprite * >(player->widget.get());
    pitch.widget->addChild(player->widget);
    pitch.widget->addChild(sprite->getShadow());
    engine->addEntity(player.get());
    player->shirt_number = i + 1;

    if (i >= 10) {
      team1.addPlayer(player.get());
    } else {
      team2.addPlayer(player.get());
    }

    // need to move out of loop scope or smart pointer will be destroyed
    players.emplace_back(std::move(player));
  }

  // ball
  std::unique_ptr< Ball > ball = BallFactory::makeBall("ball");
  auto *ballsprite = dynamic_cast< Sprite * >(ball->widget.get());
  ball->position.x = 300;
  ball->position.y = 300;
  pitch.widget->addChild(ballsprite->getShadow());
  pitch.widget->addChild(ball->widget);

  // add entities to engine
  engine->addEntity(&match);
  engine->addEntity(&team1);
  engine->addEntity(&team2);
  engine->addEntity(&pitch);
  engine->addEntity(ball.get());

  // there is a circular relationship engine <-> viewer
  engine->connectViewer(viewer);
  viewer.get()->connectEngine(engine);

  Player::ball = ball.get();
  Player::pitch = &pitch;

  team1.init();
  // test
  for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
    if (sf::Joystick::isConnected(i)) {
      sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
      std::cout << i << " connected : " << id.name.toAnsiString() << std::endl;
    }
  }

  // camera
  engine->camera.init(800, 600);
  engine->camera.setWorldRect(sf::Rect< int >(0, 0, 1900, 2600));
  engine->camera.follow(ball.get());
  ball->bounds.setSize(sf::Vector2f(1900, 2600));

  viewer.get()->startup();
  float timestep = 0.01f; // optimal for semi-implicit euler
  while (viewer.get()->running) {
    // debug ui
    debug.update();
    controller.update();
    engine->frame(timestep);
    viewer.get()->frame();
  }
  ImGui::SFML::Shutdown();
  viewer.get()->close();

  return 0;
}
