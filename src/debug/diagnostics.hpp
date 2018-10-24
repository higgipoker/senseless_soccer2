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
#pragma once

#include "../player/player.hpp"
#include <gamelib2/debug/diagnostic.hpp>

namespace senseless_soccer {

class Diagnostic : public gamelib2::Diagnostic {
public:
  void update() override;
  void selectEntity(Entity *entity) override;
  void deSelect() override;
  void showPlayerMenu();

private:
  Player *selected_player = nullptr;
  void process_animation_list(std::vector<const char *> &out_list,
                              int &out_active_index);

  void process_brainstate_list(std::vector<const char *> &out_list,
                               int &out_active_index);
};

} // namespace senseless_soccer
