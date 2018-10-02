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
#include <gamelib2/math/vector.hpp>
#include <gamelib2/utils/files.hpp>
#include <gamelib2/viewer/viewer.hpp>
#include <gamelib2/widgets/sprite.hpp>
#include <gamelib2/widgets/spriteanimation.hpp>
#include <gamelib2/widgets/tiledscrollingbackground.hpp>

#include "ball/ball_factory.hpp"
#include "pitch/pitch.hpp"
#include "player/player.hpp"
#include "player/playerfactory.hpp"

using namespace gamelib2;
using namespace senseless_soccer;

int main() {
    Viewer viewer;
    Engine engine;
    std::string dir = Files::getWorkingDirectory();

    // inits static stuff
    Player::Init();

    // set up a controller from a keyboard inpout
    std::unique_ptr<Keyboard> keyboard(new Keyboard());
    Controller controller(std::move(keyboard));

    // scrolling background
    std::shared_ptr<gamelib2::Entity> tile_entity =
      std::make_shared<Pitch>("background");
    WidgetPtr tiledbg =
      std::make_shared<TiledScrollingBackground>(dir + "/gfx/grass_dry.png");

    tiledbg->connectEntity(tile_entity);
    tile_entity->connectWidget(tiledbg);
    viewer.addWidget(tiledbg.get());

    // players
    for (int i = 0; i < 30; ++i) {
        std::shared_ptr<gamelib2::Entity> player;
        std::stringstream name;
        name << "player" << i;
        PlayerFactory::makePlayer(name.str(), player);
        // tiledbg->addChild(player_shadow);
        // tiledbg->addChild(player_sprite);
        engine.addEntity(player);
        if (i == 0) {
            controller.setListener(dynamic_cast<Player *>(player.get()));
        }
    }

    // ball
    std::shared_ptr<gamelib2::Entity> ball;
    std::shared_ptr<gamelib2::Widget> ball_sprite;
    std::cout << ball_sprite.use_count() << std::endl;
    std::shared_ptr<gamelib2::Widget> ball_shadow;
    BallFactory::makeBall("ball", ball, ball_sprite, ball_shadow);
    std::cout << ball_sprite.use_count() << std::endl;

    tiledbg->addChild(ball_shadow.get());
    tiledbg->addChild(ball_sprite.get());
    std::cout << ball_sprite.use_count() << std::endl;

    // add entities to engine

    engine.addEntity(ball);
    engine.addEntity(tile_entity);

    // there is a circular relationship between engine <-> viewer
    engine.connectViewer(&viewer);
    viewer.connectEngine(&engine);

    Player::ball = std::dynamic_pointer_cast<Ball>(ball);

    viewer.startup();
    while (viewer.running) {
        controller.update();
        engine.frame(0.01f);
        viewer.run();
    }
    viewer.close();

    std::cout << ball_sprite.use_count() << std::endl;

    return 0;
}
