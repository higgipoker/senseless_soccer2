
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
#include "pitch/pitch.hpp"
#include "player/player.hpp"
#include "player/playerfactory.hpp"

using namespace gamelib2;
using namespace senseless_soccer;

static Viewer viewer;
static gamelib2::Engine engine;
static std::promise<void> exitSignal;
static std::future<void> futureObj;
static std::thread *viewer_thread;

void start_viewer(Viewer &viewer) {
    viewer.startup();
    futureObj = exitSignal.get_future();
    viewer_thread =
      new std::thread(&Viewer::run, &viewer, std::move(futureObj));
    viewer_thread->detach();
}

void stop_viewer() {
    viewer.close();
    exitSignal.set_value();
    usleep(100);
    delete viewer_thread;
}

int main() {
    std::string dir = Files::getWorkingDirectory();

    // inits static stuff
    Player::Init();

    // keyboard to handle inputs
    auto keyboard = std::make_shared<Keyboard>();

    // scrolling background
    std::shared_ptr<gamelib2::Entity> tile_entity =
      std::make_shared<Pitch>("background");
    WidgetPtr tiledbg =
      std::make_shared<TiledScrollingBackground>(dir + "/gfx/grass_dry.png");

    std::weak_ptr<gamelib2::Entity> t = tile_entity;
    std::weak_ptr<gamelib2::Widget> s = tiledbg;
    tiledbg->connectEntity(t);
    tile_entity->connectWidget(s);

    // player
    std::shared_ptr<gamelib2::Entity> player;
    std::shared_ptr<gamelib2::Widget> player_sprite;
    std::shared_ptr<gamelib2::Widget> player_shadow;
    PlayerFactory::makePlayer("player1", player, player_sprite, player_shadow);

    // ball
    std::shared_ptr<gamelib2::Entity> ball;
    std::shared_ptr<gamelib2::Widget> ball_sprite;
    std::shared_ptr<gamelib2::Widget> ball_shadow;
    BallFactory::makeBall("ball", ball, ball_sprite, ball_shadow);

    std::weak_ptr<gamelib2::Keyboard> kb = keyboard;
    viewer.connectKeyboard(kb);
    player->connectKeyboard(kb);

    // add the widgets to the viewer
    viewer.addWidget(tiledbg);
    viewer.addWidget(player_sprite);
    viewer.addWidget(player_shadow);
    viewer.addWidget(ball_sprite);
    viewer.addWidget(ball_shadow);

    // add entities to engine
    engine.addEntity(player);
    engine.addEntity(ball);
    engine.addEntity(tile_entity);

    // there is a circular relationship between engine <-> viewer
    engine.connectViewer(&viewer);
    viewer.connectEngine(&engine);

    // start the game!
    start_viewer(viewer);
    while (viewer.running) {
        engine.frame(0.01f);
    }
    stop_viewer();

    std::cout << tiledbg.use_count() << std::endl;
    std::cout << player.use_count() << std::endl;
    std::cout << ball.use_count() << std::endl;

    return 0;
}
