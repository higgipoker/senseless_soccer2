#include <iostream>
#include <memory>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

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

#include "memory/ballfactory.hpp"
#include "pitch/pitch.hpp"
#include "player/player.hpp"
#include "memory/playerfactory.hpp"
#include "team/team.hpp"

using namespace gamelib2;
using namespace senseless_soccer;

int main() {
    Viewer viewer;
    Engine engine;
    Team team1("team1");

    std::string dir = Files::getWorkingDirectory();

    // inits static stuff
    Player::Init();

    // set up a controller from a keyboard inpout
    XboxController xbox_controller;
    Keyboard keyboard;
    SensiController controller(xbox_controller);
    team1.controller = &controller;

    // scrolling background
    std::unique_ptr<Entity> tile_entity = std::make_unique<Pitch>("background");
    std::unique_ptr<Widget> tiledbg =
      std::make_unique<TiledScrollingBackground>(dir + "/gfx/grass_dry.png");
    tiledbg->z_order = -10;
    tiledbg->connectEntity(tile_entity.get());
    tile_entity->connectWidget(std::move(tiledbg));
    viewer.addWidget(tile_entity->widget.get());

    // test
    Widget *l = static_cast<Widget *>(&controller.label);
    tile_entity->widget.get()->addChild(l);

    // players
    std::vector<std::unique_ptr<Player>> players;
    for (int i = 0; i < 2; ++i) {
        std::stringstream name;
        name << "player" << i;
        auto player = PlayerFactory::makePlayer(name.str());
        tile_entity->widget.get()->addChild(player->widget.get());
        Widget *w = player->widget.get();
        Sprite *s = static_cast<Sprite *>(w);
        tile_entity->widget.get()->addChild(s->getShadow());
        engine.addEntity(player.get());
        if (i == 0) {
            player->attachInput(&controller);
            controller.attachToPlayer(player.get());
        }

        team1.addPlayer(player.get());
        players.emplace_back(std::move(player));
    }

    // ball
    std::unique_ptr<Ball> ball = BallFactory::makeBall("ball");
    Sprite *ballsprite = static_cast<Sprite *>(ball->widget.get());
    tile_entity->widget.get()->addChild(ballsprite->getShadow());
    tile_entity->widget.get()->addChild(ballsprite);
    ball->bounds.setSize(sf::Vector2f(800, 600));

    // add entities to engine
    engine.addEntity(ball.get());
    engine.addEntity(tile_entity.get());

    // there is a circular relationship between engine <-> viewer
    engine.connectViewer(&viewer);
    viewer.connectEngine(&engine);

    Player::ball = ball.get();

    viewer.startup();
    float timestep = 0.01f; // optimal for semi-implicit euler
    while (viewer.running) {
        team1.update(timestep);
        controller.update();
        engine.frame(timestep);
        viewer.frame();
    }
    viewer.close();

    return 0;
}
