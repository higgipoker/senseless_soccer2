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
using namespace team;

int main() {
  // main game objects
  auto viewer = std::make_shared<Viewer>();
  auto engine = std::make_shared<Engine>();
  auto pitch = std::make_shared<Pitch>();
  auto match = std::make_shared<Match>();
  auto ball = BallFactory::makeBall("ball");
  auto team1 = std::make_shared<team::Team>("team1");
  auto team2 = std::make_shared<team::Team>("team2");

  engine->camera.setPosition(pitch->dimensions.center +
                             Vector3(0, pitch->dimensions.bounds.height / 2));

  team1->kit = Kit::make_standard_blue_kit();
  team2->kit = Kit::make_standard_red_kit();

  // match->init(team1, team2);
  match->init(team1, team2, pitch, ball);

  // a debug hud
  senseless_soccer::Diagnostic debug(viewer);
  viewer->connectDiagnostics(debug);

  // inits static stuff
  Player::init();

  // set up a controller from a keyboard inpout
  XboxController xbox_controller;
  Keyboard keyboard;
  SensiController controller(keyboard);
  team1->controller = &controller;

  // scrolling background
  std::shared_ptr<PitchWidget> pitch_widget = std::make_shared<PitchWidget>(
      Files::getWorkingDirectory() + "/gfx/grass_horizontal.png",
      engine->camera);
  pitch_widget->z_order = -10;
  pitch_widget->connectEntity(pitch);
  pitch->connectWidget(std::move(pitch_widget));
  viewer.get()->addWidget(pitch->widget);

  // test
  pitch->widget->addChild(controller.label);

  // players
  std::vector<std::shared_ptr<Player> > players;
  for (int i = 0; i < 22; ++i) {
    std::stringstream name;
    name << "player" << i;
    auto player = PlayerFactory::makePlayer(name.str());
    auto *sprite = dynamic_cast<Sprite *>(player->widget.get());
    pitch->widget->addChild(player->widget);
    pitch->widget->addChild(sprite->getShadow());
    engine->addEntity(player);
    player->shirt_number = i + 1;

    if (i >= 11) {
      team1->addPlayer(player);
    } else {
      team2->addPlayer(player);
    }

    // need to move out of loop scope or smart pointer will be destroyed
    players.emplace_back(std::move(player));
  }

  // ball
  auto *ballsprite = dynamic_cast<Sprite *>(ball->widget.get());
  ball->position.x = 300;
  ball->position.y = 300;
  pitch->widget->addChild(ballsprite->getShadow());
  pitch->widget->addChild(ball->widget);

  // add entities to engine
  engine->addEntity(match);
  engine->addEntity(team1);
  engine->addEntity(team2);
  engine->addEntity(pitch);
  engine->addEntity(ball);

  // there is a circular relationship engine <-> viewer
  engine->connectViewer(viewer);
  viewer.get()->connectEngine(engine);

  // todo move to match
  Player::ball = ball.get();
  Player::pitch = pitch.get();

  team::Position::scanPositions();
  team1->init(pitch, Direction::NORTH);
  team2->init(pitch, Direction::SOUTH);

  // test
  for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
    if (sf::Joystick::isConnected(i)) {
      sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
      std::cout << "Joystick " << i << " connected : " << id.name.toAnsiString()
                << std::endl;
    }
  }

  // camera
  engine->camera.init(800, 600);
  engine->camera.setWorldRect(sf::Rect<int>(0, 0, 2000, 3000));
  engine->camera.follow(ball.get());
  ball->bounds.setSize(sf::Vector2f(2000, 3000));
  ball->setPosition(pitch->dimensions.center);

  viewer->startup();
  float timestep = 0.01f;  // optimal for semi-implicit euler
  while (viewer.get()->running) {
    // debug ui
    debug.update();
    controller.update();
    match->update(0.01f);
    engine->frame(timestep);
    viewer.get()->frame();
  }
  ImGui::SFML::Shutdown();
  viewer.get()->close();

  return 0;
}
