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

  // shirt number
  ImGui::Text("Shirt: %i", selected_player->shirt_number);

  // player state
  ImGui::Text("State: %s", selected_player->stateName().c_str());

  // animation
  std::vector<const char *> animations;
  for (auto &anim : selected_player->widget->animations) {
    animations.emplace_back(anim.first.c_str());
  }
  static const char *item_current =
      selected_player->widget->currentAnimation()->name.c_str();

  if (ImGui::BeginCombo("animation", item_current)) {
    for (int n = 0; n < animations.size(); n++) {
      bool is_selected = (item_current == animations[n]);
      if (ImGui::Selectable(animations[n], is_selected))
        item_current = animations[n];
      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    selected_player->widget->startAnimation(item_current);
    ImGui::EndCombo();
  }
  ImGui::End();

  // speed
  // veclcity
  // acceleration
  // position
  // name
  // team
  // shirt number
}
} // namespace senseless_soccer
