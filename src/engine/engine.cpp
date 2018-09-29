//#include "engine.hpp"

//#include <cstdio>  // defines FILENAME_MAX

//#include <iostream>

//#include <algorithm>
//#include <gamelib2/utils/fps.hpp>

// namespace senseless_soccer {
// using namespace gamelib2;

////
///----------------------------------------------------------------------------
//// sort predicate for sprites
////
///----------------------------------------------------------------------------
// struct {
//  bool operator()(const SpritePtr &s1, SpritePtr &s2) const {
//    return s1.get()->z_order < s2.get()->z_order;
//  }
//} sort_sprites;

// void fps() {
//  FPS::update();
//  std::cout << FPS::getFPS() << std::endl;
//}

////
///----------------------------------------------------------------------------
//// run
////
///----------------------------------------------------------------------------
// void Engine::run() {
//  init();
//  do {
//    input();
//    update();
//    // render();
//    // fps();

//  } while (running);
//  shutdown();
//}

////
///----------------------------------------------------------------------------
//// init
////
///----------------------------------------------------------------------------
// void Engine::init() {
//  running = true;
//}

////
///----------------------------------------------------------------------------
//// input
////
///----------------------------------------------------------------------------
// void Engine::input() {

//}

////
///----------------------------------------------------------------------------
//// update
////
///----------------------------------------------------------------------------
// void Engine::update() {
//  for (auto &entity : entities) {
//    entity->update();
//  }
//}

////
///----------------------------------------------------------------------------
//// draw
////
///----------------------------------------------------------------------------
// void Engine::render() {

//}

////
///----------------------------------------------------------------------------
//// shutdown
////
///----------------------------------------------------------------------------
// void Engine::shutdown() {
//  std::cout << "Shutting down Game Engine" << std::endl;
//}

////
///----------------------------------------------------------------------------
//// addRenderable
////
///----------------------------------------------------------------------------
// void Engine::addSprite(size_t layer, SpritePtr &in_sprite) {
//  while (render_layers.size() <= layer) {
//    render_layers.emplace_back(RenderLayer());
//  }

//  render_layers[layer].sprites.emplace_back(in_sprite);
//}

////
///----------------------------------------------------------------------------
//// remRenderable
////
///----------------------------------------------------------------------------
// void Engine::remSprite(size_t layer, SpritePtr &in_sprite) {
//  if (render_layers.size() >= layer) {
//    render_layers[layer].sprites.erase(
//        std::remove(render_layers[layer].sprites.begin(),
//                    render_layers[layer].sprites.end(), in_sprite),
//        render_layers[layer].sprites.end());
//  }
//  in_sprite.reset();
//}

////
///----------------------------------------------------------------------------
//// addRenderable
////
///----------------------------------------------------------------------------
// void Engine::addPlayer(PlayerPtr &in_entity) {
//  entities.emplace_back(in_entity);
//}

////
///----------------------------------------------------------------------------
//// remRenderable
////
///----------------------------------------------------------------------------
// void Engine::remPlayer(PlayerPtr &in_entity) {
//  entities.erase(std::remove(entities.begin(), entities.end(), in_entity),
//                 entities.end());
//}
//}  // namespace senseless_soccer
