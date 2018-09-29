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
#include <gamelib2/graphics/sprite.hpp>
#include <gamelib2/graphics/spriteanimation.hpp>
#include <gamelib2/graphics/tiledscrollingbackground.hpp>
#include <gamelib2/input/keyboard.hpp>
#include <gamelib2/math/vector.hpp>
#include <gamelib2/utils/files.hpp>
#include <gamelib2/viewer/viewer.hpp>

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
}

void stop_viewer() {
    exitSignal.set_value();
    viewer_thread->join();
    delete viewer_thread;
}

int main() {

    // keyboard to handle inputs
    auto kb = std::make_shared<Keyboard>();

    // scrolling background
    auto tile_entity = std::make_shared<Entity>("background");
    WidgetPtr tiledbg = std::make_shared<TiledScrollingBackground>(
      Files::getWorkingDirectory() + "/gfx/grass_dry.png");
    tiledbg->connectEntity(tile_entity);

    // inputs come into the screen, but handled by the engine
    viewer.connectKeyboard(kb);

    for (int i = 0; i < 10; ++i) {
        std::ostringstream name;
        name << "player" << i;
        std::shared_ptr<Entity> player = PlayerFactory::makePlayer(name.str());
        engine.addEntity(player);
        tiledbg->addChild(player->widget);
        if (i == 0) {
            player->connectKeyboard(kb);
        }
    }

    // add the widgets to the viewer
    viewer.addWidget(tiledbg);

    // there is a circular relationship between engine <-> viewer
    engine.connectViewer(&viewer);
    viewer.connectEngine(&engine);

    // start the game!
    start_viewer(viewer);
    while (viewer.running) {
        engine.frame(0.01f);
    }
    stop_viewer();

    return 0;
}
