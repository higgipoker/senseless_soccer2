
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <unistd.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <gamelib2/engine/engine.hpp>
#include <gamelib2/game/entity.hpp>
#include <gamelib2/graphics/autotexture.hpp>
#include <gamelib2/input/keyboard.hpp>
#include <gamelib2/math/vector.hpp>
#include <gamelib2/utils/files.hpp>
#include <gamelib2/viewer/viewer.hpp>
#include <gamelib2/widgets/sprite.hpp>
#include <gamelib2/widgets/spriteanimation.hpp>
#include <gamelib2/widgets/tiledscrollingbackground.hpp>

#include "ball/ball_factory.hpp"
#include "player/player.hpp"
#include "player/playerfactory.hpp"

using namespace gamelib2;
using namespace senseless_soccer;

void start_viewer(Viewer &viewer) {
}

void stop_viewer() {
}

int main() {
    static Viewer viewer;
    static gamelib2::Engine engine;
    static std::promise<void> exitSignal;
    static std::future<void> futureObj;
    static std::thread *viewer_thread;

    // inits static stuff
    Player::Init();

    // keyboard to handle inputs
    auto kb = std::make_shared<Keyboard>();

    // scrolling background
    auto tile_entity = std::make_shared<Entity>("background");
    WidgetPtr tiledbg = std::make_shared<TiledScrollingBackground>(
      Files::getWorkingDirectory() + "/gfx/grass_dry.png");

    std::weak_ptr<gamelib2::Entity> t = tile_entity;
    tiledbg->connectEntity(t);

    // player
    std::shared_ptr<gamelib2::Entity> player;
    std::shared_ptr<gamelib2::Widget> sprite;
    PlayerFactory::makePlayer("player1", player, sprite);

    // ball
    std::shared_ptr<gamelib2::Entity> ball;
    std::shared_ptr<gamelib2::Widget> ball_sprite;
    BallFactory::makeBall("ball", ball, ball_sprite);

    std::weak_ptr<gamelib2::Keyboard> keyboard = kb;
    viewer.connectKeyboard(keyboard);
    player->connectKeyboard(keyboard);

    // add the widgets to the viewer
    viewer.addWidget(tiledbg);
    viewer.addWidget(sprite);
    viewer.addWidget(ball_sprite);

    // add entities to engine
    engine.addEntity(player);
    engine.addEntity(ball);

    // there is a circular relationship between engine <-> viewer
    engine.connectViewer(&viewer);
    viewer.connectEngine(&engine);

    // start the game!
    viewer.startup();
    futureObj = exitSignal.get_future();
    viewer_thread =
      new std::thread(&Viewer::run, &viewer, std::move(futureObj));
    viewer_thread->detach();
    while (viewer.running) {
        engine.frame(0.01f);
    }
    viewer.close();
    exitSignal.set_value();
    usleep(100);
    delete viewer_thread;

    std::cout << tiledbg.use_count() << std::endl;
    std::cout << player.use_count() << std::endl;
    std::cout << ball.use_count() << std::endl;

    return 0;
}
