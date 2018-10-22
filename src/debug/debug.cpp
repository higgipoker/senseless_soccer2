///****************************************************************************
// * Copyright (c) 2018 P. Higgins
// *
// * This software is provided 'as-is', without any express or implied
// * warranty. In no event will the authors be held liable for any damages
// * arising from the use of this software.
// *
// * Permission is granted to anyone to use this software for any purpose,
// * including commercial applications, and to alter it and redistribute it
// * freely, subject to the following restrictions:
// *
// * 1. The origin of this software must not be misrepresented; you must not
// *    claim that you wrote the original software. If you use this software
// *    in a product, an acknowledgment in the product documentation would be
// *    appreciated but is not required.
// * 2. Altered source versions must be plainly marked as such, and must not be
// *    misrepresented as being the original software.
// * 3. This notice may not be removed or altered from any source distribution.
// ****************************************************************************/
//#include "debug.hpp"

//#include <gamelib2/widgets/widget.hpp>
//#include <sstream>
// namespace senseless_soccer {

////
///-----------------------------------------------------------------------------
////
////
///-----------------------------------------------------------------------------
// Debug::Debug() {}

////
///-----------------------------------------------------------------------------
////
////
///-----------------------------------------------------------------------------
// void Debug::drawPlayerPanel() {
//  // test

//  gamelib2::Widget &widget = *player->widget;
//  /////////////////////////////////////////////////////////////////////////////
//  /// name
//  /////////////////////////////////////////////////////////////////////////////
//  ImGui::NewLine();
//  ImGui::Bullet();
//  std::ostringstream name;
//  name << widget.getName() << " ("
//       << static_cast<int>(widget.entity->position.x) << ", "
//       << static_cast<int>(widget.entity->position.y) << ", "
//       << static_cast<int>(widget.entity->position.z) << ")";
//  ImGui::Text("%s", name.str().c_str());

//  /////////////////////////////////////////////////////////////////////////////
//  /// animations dropdown
//  /////////////////////////////////////////////////////////////////////////////
//  static int item_current = 0;
//  std::vector<const char *> items;
//  std::map<SpriteAnimation *, int> anim_map;
//  size_t i = 0;
//  for (auto &animation : widget.animations) {
//    items.push_back(animation.first.c_str());
//    anim_map.insert(std::make_pair(&animation.second, i++));
//  }
//  items.push_back("none");

//  // need to get the index of active animation
//  SpriteAnimation *anim = widget.currentAnimation();
//  if (anim) {
//    item_current = anim_map[anim];
//  } else {
//    item_current = static_cast<int>(items.size() - 1);
//  }

//  ImGui::Combo("animation", &item_current, &items[0],
//               static_cast<int>(items.size()));
//  const std::string anim_name(items[static_cast<unsigned int>(item_current)]);
//  if (anim_name == "none") {
//    widget.stopAnimation();
//  } else {
//    if (widget.currentAnimation()) {
//      if (widget.currentAnimation()->name != anim_name) {
//        widget.startAnimation(anim_name);
//      }
//    } else {
//      widget.startAnimation(anim_name);
//    }
//  }

//  /////////////////////////////////////////////////////////////////////////////
//  /// scaling
//  /////////////////////////////////////////////////////////////////////////////
//  scale = widget.scale();
//  ImGui::SliderFloat("scale", &scale, 0.0f, 10.0f, "%.1f");
//  widget.scale(scale, scale);
//}

////
///-----------------------------------------------------------------------------
////
////
///-----------------------------------------------------------------------------
// void Debug::update(float dt) {
//  if (player_panel_visible) {
//    drawPlayerPanel();
//  }
//}

////
///-----------------------------------------------------------------------------
////
////
///-----------------------------------------------------------------------------
// void Debug::showPlayerPanel(Player *player) { player_panel_visible = true; }

////
///-----------------------------------------------------------------------------
////
////
///-----------------------------------------------------------------------------
// void Debug::hidePlayerPanel() { player_panel_visible = false; }
//} // namespace senseless_soccer
