/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#include "diagnostics.hpp"
#include "../player/ai/brain.hpp"
#include "../player/locomotion/locomotionmanager.hpp"

#include <gamelib2/viewer/viewer.hpp>
#include <gamelib2/widgets/widget.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <sstream>
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// Diagnostic
// -----------------------------------------------------------------------------
Diagnostic::Diagnostic(Game &_in_game) : gamelib2::Diagnostic(_in_game) {}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Diagnostic::update() {
  if (on) {
    gamelib2::Diagnostic::update();
    // dimensions
//     panel_dimensions.width = last_panel_dimensions.width;
//     panel_dimensions.height =
//         game.viewer.getWindow().getSize().y - last_panel_dimensions.height;
//     panel_dimensions.left =
//         game.viewer.getWindow().getSize().x - panel_dimensions.width;
//     panel_dimensions.top =
//         last_panel_dimensions.top + last_panel_dimensions.height;
//
//     ImGui::SetNextWindowSize(
//         sf::Vector2f(panel_dimensions.width, panel_dimensions.height));
//     ImGui::SetNextWindowPos(
//         sf::Vector2f(panel_dimensions.left, panel_dimensions.top));

    // entity window
    if (selected_entity) {
      ImGui::Begin(selected_entity->name.c_str());
      showEntityMenu();
      if (selected_entity->type == "player") {
        showPlayerMenu();
      }else if(selected_entity->type == "ball"){
        showBallMenu();
      }
      //last_panel_dimensions = panel_dimensions;
      ImGui::End();
    }
  }
}

// -----------------------------------------------------------------------------
// selectEntity
// -----------------------------------------------------------------------------
void Diagnostic::selectEntity(Entity *e) {
  gamelib2::Diagnostic::selectEntity(e);
  if (e->type == "player") {
    if (selected_player != e) {
      selected_player = e;
    }
  } else {
    selected_player = nullptr;
  }
}

// -----------------------------------------------------------------------------
// deSelect
// -----------------------------------------------------------------------------
void Diagnostic::deSelect() { selected_player = nullptr; }

// -----------------------------------------------------------------------------
// showEntityMenu
// -----------------------------------------------------------------------------
void Diagnostic::showEntityMenu() {
  ImGui::Text("Position");
  ImGui::Text("x: %f", selected_entity->position.x);
  ImGui::Text("y: %f", selected_entity->position.y);
  ImGui::Text("z: %f", selected_entity->position.z);
  ImGui::Text("_____________________________________");

  ImGui::Text("Velocity");
  ImGui::Text("x: %f", selected_entity->velocity.x);
  ImGui::Text("y: %f", selected_entity->velocity.y);
  ImGui::Text("z: %f", selected_entity->velocity.z);
  ImGui::Text("_____________________________________");
}

// -----------------------------------------------------------------------------
// showPlayerMenu
// -----------------------------------------------------------------------------
void Diagnostic::showPlayerMenu() {
  // player widgets
  ImGuiStyle &style = ImGui::GetStyle();

  auto &player = static_cast<Player &>(*selected_player);

  ImGui::Text("Player");

  // shirt number
  ImGui::Text("Shirt Number: %i", player.shirt_number);

  // player state
  ImGui::Text("Player State: %s", player.stateName().c_str());

  // player role
  if (player.role) {
    ImGui::Text("Position: %s", player.role->name.c_str());
  }

  {  // animation
    if (player.controller != nullptr) {
      if(player.widget->currentAnimation()){
        int active_anim_index = 0;
        std::string orig_anim = player.widget->currentAnimation()->name;
        std::vector<const char *> anims;
        process_animation_list(anims, active_anim_index);
        ImGui::Combo("##animation", &active_anim_index, anims.data(),
                    anims.size());
        if (orig_anim != anims[active_anim_index]) {
          std::string new_anim = anims[active_anim_index];
          player.widget->startAnimation(new_anim);
        }
      }
    } else {
      if (player.widget->currentAnimation()) {
        ImGui::Text("Animation: %s",
                    player.widget->currentAnimation()->name.c_str());
      }
    }
  }

  // these things mean nothing if an input is attached
  if (player.controller != nullptr) {
    style.Alpha = 0.2f;
    // brainstate
    ImGui::Text("Brainstate: input attached");

    // locomotion
    ImGui::Text("Locomotion: input attached");

  } else {
    {  // brain state
      int active_state_index = 0;
      std::string orig_state = player.brain.currentState();
      std::vector<const char *> states;
      process_brainstate_list(states, active_state_index);
      ImGui::Combo("##Brainstate", &active_state_index, states.data(),
                   states.size());
      if (orig_state != states[active_state_index]) {
        ai::State new_state = ai::Brain::state_map[states[active_state_index]];
        player.brain.changeState(new_state);
      }
    }

    {  // locomotion
      ImGui::Text("Locomotion: %s",
                  player.brain.locomotion.currentLocomotion().name.c_str());
      if (player.brain.locomotion.currentLocomotion()
              .diagnosticParamaters()
              .length()) {
        ImGui::SameLine();
        ImGui::Text("(%s)", player.brain.locomotion.currentLocomotion()
                                .diagnosticParamaters()
                                .c_str());
      }
    }
  }
  style.Alpha = 1.0f;
  ImGui::Text("_____________________________________");
}

// -----------------------------------------------------------------------------
// showBallMenu
// -----------------------------------------------------------------------------
void Diagnostic::showBallMenu(){

  ImGuiStyle &style = ImGui::GetStyle();
  auto &ball = static_cast<Ball &>(*selected_entity);
  ImGui::Text("Physical Environment");

  ImGui::SliderFloat("gravity", &ball.environment.gravity, 0.0f, 1000.0f);
  ImGui::SliderFloat("friction", &ball.environment.co_friction, 0.0f, 1.0f);
  ImGui::SliderFloat("bounce", &ball.environment.co_bounciness, 0.0f, 1.0f);

  ImGui::Text("_____________________________________");

  ImGui::Text("Forces");
  ImGui::SliderFloat("x", &ball_x, 0.0f, 10000.0f);
  ImGui::SliderFloat("y", &ball_y, 0.0f, 10000.0f);
  ImGui::SliderFloat("z", &ball_z, 0.0f, 10000.0f);
  if (ImGui::Button("Apply Force")){
    ball.kick(gamelib2::Vector3(ball_x, ball_y, ball_z));
  }

  ImGui::Text("_____________________________________");
}

// -----------------------------------------------------------------------------
// process_animation_list
// -----------------------------------------------------------------------------
void Diagnostic::process_animation_list(std::vector<const char *> &out_list,
                                        int &out_active_index) {
  auto current_anim = selected_player->widget->currentAnimation();

  int idx = 0;
  for (auto &anim : selected_player->widget->animations) {
    out_list.emplace_back(anim.first.c_str());
    if (anim.first == current_anim->name) {
      out_active_index = idx;
    }
    idx++;
  }
}

// -----------------------------------------------------------------------------
// process_brainstate_list
// -----------------------------------------------------------------------------
void Diagnostic::process_brainstate_list(std::vector<const char *> &out_list,
                                         int &out_active_index) {
  int idx = 0;
  for (auto &state : ai::Brain::state_map) {
    out_list.emplace_back(state.first.c_str());
    auto &player = static_cast<Player &>(*selected_player);
    if (player.brain.currentState() == state.first) {
      out_active_index = idx;
    }
    idx++;
  }
}

// -----------------------------------------------------------------------------
// onClose
// -----------------------------------------------------------------------------
void Diagnostic::onClose() { ImGui::SFML::Render(game.viewer.getWindow()); }
}  // namespace senseless_soccer
