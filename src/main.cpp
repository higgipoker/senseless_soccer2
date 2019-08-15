#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <iostream>
#include <memory>
#include <sstream>

#include <gamelib2/game/entity.hpp>
#include <gamelib2/game/game.hpp>
#include <gamelib2/input/keyboard.hpp>
#include <gamelib2/input/xbox_gamepad.hpp>
#include <gamelib2/utils/files.hpp>

#include <gamelib2/imgui/imgui-SFML.h>
#include <gamelib2/imgui/imgui.h>

#include "ball/ball_animations.hpp"
#include "ball/ballfactory.hpp"
#include "debug/diagnostics.hpp"
#include "match/match.hpp"
#include "pitch/pitch.hpp"
#include "pitch/pitchwidget.hpp"
#include "player/player_animations.h"
#include "player/playerfactory.hpp"
#include "team/kit.hpp"
#include "team/team.hpp"

using namespace gamelib2;
using namespace senseless_soccer;
using namespace match;
using namespace team;

// a mouse entity for the camera to follow
class Mouse : public Entity {
 public:
  Mouse(sf::RenderWindow &in_window) : window(in_window) {}
  virtual void onDragged(const Vector3 &diff) {}
  virtual void update(float dt) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
      // convert it to world coordinates
      sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
      setPosition(worldPos.x, worldPos.y);
    }
  }

 private:
  sf::RenderWindow &window;
};

void print_controllers() {
  for (int i = 0; i < sf::Joystick::Count; ++i) {
    if (sf::Joystick::isConnected(i)) {
      sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
      std::cout << "Joystick " << i << " connected : " << id.name.toAnsiString()
                << std::endl;
    }
  }
}

int main() {
  std::string working_dir = Files::getWorkingDirectory();
  std::string gfx_path = working_dir + "/gfx/";

  std::vector<std::string> joystick_debug_files = {
      gfx_path + "joysticker/bg.png",
      gfx_path + "joysticker/dpad_left.png",
      gfx_path + "joysticker/dpad_right.png",
      gfx_path + "joysticker/dpad_up.png",
      gfx_path + "joysticker/dpad_down.png",
      gfx_path + "joysticker/dpad_centered.png",
      gfx_path + "joysticker/button_green.png",
      gfx_path + "joysticker/button_red.png",
      gfx_path + "joysticker/button_yellow.png",
      gfx_path + "joysticker/button_blue.png",
      gfx_path + "joysticker/analog_left.png",
      gfx_path + "joysticker/analog_right.png",
  };

  // game
  Game game;

  // mouse entity (can be attached to by camera)
  Mouse mouse(game.viewer.getWindow());
  Widget dummy;
  Game::connect(&mouse, &dummy);
  game.engine.addEntity(&mouse);

  // teams
  Team team1("team1");
  Team team2("team2");
  team1.kit = team::Kit::make_standard_red_kit();
  team2.kit = team::Kit::make_standard_blue_kit();

  // pitch
  Pitch pitch;
  PitchWidget pitch_widget(gfx_path + "grass_horizontal.png", game.camera);
  pitch_widget.z_order = -10;
  Game::connect(&pitch, &pitch_widget);
  game.engine.addEntity(&pitch);
  game.viewer.addWidget(&pitch_widget);

  // ball
  Ball ball("ball");
  Sprite sprite;
  Sprite shadow;
  BallFactory::make_ball(&ball, &sprite, &shadow);
  ball.setPosition(gamelib2::Vector3(300, 300, 0));
  game.engine.addEntity(&ball);
  pitch_widget.addChild(&sprite);
  pitch_widget.addChild(&shadow);

  // players
  PlayerFactory player_factory(game.engine, game.viewer);
  Player::init();  // inits the animation frames
  Player::ball = &ball;
  Player::pitch = &pitch;

  for (int i = 0; i < 100; ++i) {
    std::stringstream player_name;
    player_name << "player" << i;
    team1.addPlayer(
        player_factory.make_player(player_name.str(), pitch_widget));
    team1.players.back()->setPosition(static_cast<float>(rand() % 800),
                                      static_cast<float>(rand() % 600));
    game.engine.addEntity(team1.players.back());
  }
  //  for (int i = 0; i < 10; ++i) {
  //    player_factory.release_player(team1.players[i]);
  //  }

  // camera
  game.camera.init(800, 600);
  game.camera.setWorldRect(sf::Rect<int>(0, 0, 2000, 3000));
  game.camera.follow(&mouse);
  // game.camera.follow(&ball);

  // debug hud
  senseless_soccer::Diagnostic debug(game);
  game.viewer.connectDiagnostics(debug);
  debug.joystick1.init(joystick_debug_files);

  // controller
  print_controllers();
  XboxController xbox_controller;
  Keyboard keyboard;
  SensiController controller(keyboard);
  // team1.controller = &controller;
  team1.players.back()->controller = &controller;
  pitch.widget->addChild(&controller.label);

  // main loop
  while (game.viewer.running) {
    controller.update();

    if (debug.active()) {
      debug.joystick1.update(controller.input.states);
      game.viewer.addWidget(&debug.joystick1, true);
    } else {
      game.viewer.remWidget(&debug.joystick1);
    }

    debug.update();
    game.update();
  }

  // cleanup
  game.viewer.close();
  return 0;
}
