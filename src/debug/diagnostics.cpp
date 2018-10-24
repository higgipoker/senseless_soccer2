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

#include <gamelib2/widgets/widget.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <sstream>
namespace senseless_soccer {

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Diagnostic::update() {
  if (selected_player) {
    showPlayerMenu();
  }
}

// -----------------------------------------------------------------------------
// selectEntity
// -----------------------------------------------------------------------------
void Diagnostic::selectEntity(Entity *entity) {
  if (entity->type == "player") {
    if (selected_player != entity) {
      selected_player = dynamic_cast<Player *>(entity);
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
// showPlayerMenu
// -----------------------------------------------------------------------------
void Diagnostic::showPlayerMenu() {

  // player window
  ImGui::Begin(selected_player->name.c_str());

  ImGuiStyle &style = ImGui::GetStyle();
  //  ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f,
  //  "%.2f");

  // shirt number
  ImGui::Text("Shirt Number: %i", selected_player->shirt_number);

  // player state
  ImGui::Text("Player State: %s", selected_player->stateName().c_str());

  { // animation
    if (selected_player->controller != nullptr) {
      int active_anim_index = 0;
      std::string orig_anim = selected_player->widget->currentAnimation()->name;
      std::vector<const char *> anims;
      process_animation_list(anims, active_anim_index);
      ImGui::Combo("animation", &active_anim_index, anims.data(), anims.size());
      if (orig_anim != anims[active_anim_index]) {
        std::string new_anim = anims[active_anim_index];
        selected_player->widget->startAnimation(new_anim);
      }
    } else {
      ImGui::Text("Animation: %s",
                  selected_player->widget->currentAnimation()->name.c_str());
    }
  }

  // these things mean nothing if an input is attached
  if (selected_player->controller != nullptr) {
    style.Alpha = 0.2f;
    // brainstate
    ImGui::Text("Brainstate: input attached");

    // locomotion
    ImGui::Text("Locomotion: input attached");

  } else {
    { // brain state
      int active_state_index = 0;
      std::string orig_state = selected_player->brain.currentState();
      std::vector<const char *> states;
      process_brainstate_list(states, active_state_index);
      ImGui::Combo("Brainstate", &active_state_index, states.data(),
                   states.size());
      if (orig_state != states[active_state_index]) {
        ai::State new_state = ai::Brain::state_map[states[active_state_index]];
        selected_player->brain.changeState(new_state);
      }
    }

    { // locomotion
      ImGui::Text(
          "Locomotion: %s",
          selected_player->brain.locomotion.currentLocomotion().name.c_str());
      if (selected_player->brain.locomotion.currentLocomotion()
              .diagnosticParamaters()
              .length()) {
        ImGui::SameLine();
        ImGui::Text("(%s)",
                    selected_player->brain.locomotion.currentLocomotion()
                        .diagnosticParamaters()
                        .c_str());
      }
    }
  }
  style.Alpha = 1.0f;
  ImGui::End();

  // speed
  // veclcity
  // acceleration
  // position
  // name
  // team
  // shirt number
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
    if (selected_player->brain.currentState() == state.first) {
      out_active_index = idx;
    }
    idx++;
  }
}
} // namespace senseless_soccer
