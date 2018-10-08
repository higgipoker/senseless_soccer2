#include <iostream>
#include <memory>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <gamelib2/engine/engine.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/graphics/autotexture.hpp>
#include <gamelib2/input/controller.hpp>
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
#include "joysticker/sensicontroller.hpp"

using namespace gamelib2;
using namespace senseless_soccer;

int main() {
    Viewer viewer;
    Engine engine;
    std::string dir = Files::getWorkingDirectory();

    // inits static stuff
    Player::Init();

    // set up a controller from a keyboard inpout
    XboxController xbox_controller;
    Keyboard keyboard;
    SensiController controller(xbox_controller);

    // scrolling background
    Entity *tile_entity = new Pitch("background");
    Widget *tiledbg = new TiledScrollingBackground(dir + "/gfx/grass_dry.png");
    tiledbg->z_order = -10;
    tiledbg->connectEntity(tile_entity);
    tile_entity->connectWidget(tiledbg);
    viewer.addWidget(tiledbg);

    // players
    for (int i = 0; i < 1; ++i) {
        std::stringstream name;
        name << "player" << i;

        Player *player = PlayerFactory::makePlayer(name.str());
        tiledbg->addChild(player->widget);
        Widget *w = player->widget;
        Sprite *s = static_cast<Sprite *>(w);
        tiledbg->addChild(s->getShadow());
        engine.addEntity(player);
        if (i == 0) {
            player->attachInput(&controller);
        }
    }

    // ball
    Ball *ball = BallFactory::makeBall("ball");
    Sprite *ballsprite = static_cast<Sprite *>(ball->widget);
    tiledbg->addChild(ballsprite->getShadow());
    tiledbg->addChild(ballsprite);

    // add entities to engine
    engine.addEntity(ball);
    engine.addEntity(tile_entity);

    // there is a circular relationship between engine <-> viewer
    engine.connectViewer(&viewer);
    viewer.connectEngine(&engine);

    Player::ball = static_cast<Ball *>(ball);

    viewer.startup();
    float timestep = 0.01f; // optimal for semi-implicit euler
    while (viewer.running) {
        controller.update();
        engine.frame(timestep);
        viewer.run();
    }
    viewer.close();

    PlayerFactory::destroy();
    BallFactory::destroy();

    delete tiledbg;
    delete tile_entity;

    return 0;
}
