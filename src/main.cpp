#include "debug/diagnostics.hpp"
#include "memory/ballfactory.hpp"
#include "memory/playerfactory.hpp"
#include "pitch/pitch.hpp"
#include "pitch/pitchwidget.hpp"
#include "player/player.hpp"
#include "team/team.hpp"

#include <gamelib2/engine/engine.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/graphics/autotexture.hpp>
#include <gamelib2/input/device.hpp>
#include <gamelib2/input/keyboard.hpp>
#include <gamelib2/input/xbox_gamepad.hpp>
#include <gamelib2/math/vector.hpp>
#include <gamelib2/utils/files.hpp>
#include <gamelib2/viewer/viewer.hpp>
#include <gamelib2/widgets/sprite.hpp>
#include <gamelib2/widgets/spriteanimation.hpp>
#include <gamelib2/widgets/tiledscrollingbackground.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <memory>
#include <sstream>

using namespace gamelib2;
using namespace senseless_soccer;

sf::Clock ui_clock;
int main() {

  Viewer viewer;
  Engine engine;

  senseless_soccer::Diagnostic debug(viewer);
  viewer.connectDiagnostics(debug);

  Team team1("team1");
  Team team2("team2");

  std::string dir = Files::getWorkingDirectory();

  // inits static stuff
  Player::init();

  // set up a controller from a keyboard inpout
  XboxController xbox_controller;
  Keyboard keyboard;
  SensiController controller(keyboard);
  team1.controller = &controller;

  // scrolling background
  std::unique_ptr<Entity> pitch_entity = std::make_unique<Pitch>("background");
  std::unique_ptr<Widget> pitch_widget = std::make_unique<PitchWidget>(
      dir + "/gfx/grass_horizontal.png", engine.camera);
  pitch_widget->z_order = -10;
  pitch_widget->connectEntity(pitch_entity.get());
  pitch_entity->connectWidget(std::move(pitch_widget));
  viewer.addWidget(pitch_entity->widget.get());

  auto pitch = dynamic_cast<Pitch *>(pitch_entity.get());
  team2.attacking_goal = pitch->dimensions.goal_north;
  team2.defending_goal = pitch->dimensions.goal_south;

  // test
  auto *l = static_cast<Widget *>(&controller.label);
  pitch_entity->widget->addChild(l);

  // players
  std::vector<std::unique_ptr<Player>> players;
  for (int i = 0; i < 2; ++i) {
    std::stringstream name;
    name << "player" << i;
    auto player = PlayerFactory::makePlayer(name.str());
    pitch_entity->widget->addChild(player->widget.get());
    auto *w = player->widget.get();
    auto *s = dynamic_cast<Sprite *>(w);
    pitch_entity->widget->addChild(s->getShadow());
    engine.addEntity(player.get());
    player->shirt_number = i + 1;
    team2.addPlayer(player.get());
    players.emplace_back(std::move(player));
  }

  // ball
  std::unique_ptr<Ball> ball = BallFactory::makeBall("ball");
  auto *ballsprite = dynamic_cast<Sprite *>(ball->widget.get());
  ball->position.x = 300;
  ball->position.y = 300;
  pitch_entity->widget->addChild(ballsprite->getShadow());
  pitch_entity->widget->addChild(ballsprite);

  // add entities to engine
  engine.addEntity(ball.get());
  engine.addEntity(pitch_entity.get());
  engine.addEntity(&team1);
  engine.addEntity(&team2);

  // there is a circular relationship between engine <-> viewer
  engine.connectViewer(&viewer);
  viewer.connectEngine(&engine);

  Player::ball = ball.get();
  Player::pitch = dynamic_cast<Pitch *>(pitch_entity.get());
  // test
  for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
    if (sf::Joystick::isConnected(i)) {
      sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
      std::cout << i << " connected : " << id.name.toAnsiString() << std::endl;
    }
  }

  // camera
  engine.camera.init(800, 600);
  engine.camera.setWorldRect(sf::Rect<int>(0, 0, 1900, 2600));
  engine.camera.follow(ball.get());
  ball->bounds.setSize(sf::Vector2f(1900, 2600));

  viewer.startup();
  float timestep = 0.01f; // optimal for semi-implicit euler
  while (viewer.running) {
    // --------------------
    // debug ui
    // --------------------
    ImGui::SFML::Update(viewer.getWindow(), ui_clock.restart());
    debug.update();

    controller.update();
    engine.frame(timestep);
    viewer.frame();
  }
  ImGui::SFML::Shutdown();
  viewer.close();

  return 0;
}
