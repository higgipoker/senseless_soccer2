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
#include "state.hpp"

#include <gamelib2/math/vector.hpp>

#include <queue>

namespace senseless_soccer {
class Player;
namespace team {

enum class MiniState { Entering, Waiting };

class EnterPitch : public State {
 public:
  EnterPitch(Team &t);
  virtual ~EnterPitch() = default;
  virtual void start() override;
  virtual void stop() override;
  virtual bool finished() override;
  virtual void update(float dt) override;

 protected:
  // line up positions to send players to
  gamelib2::Vector3 first_position;
  gamelib2::Vector3 offset;
  gamelib2::Vector3 last_position;

  void march_player();
  std::queue<Player *> marchers;
  int ticks = 0;
  int speed = 10;
  int vertical_offset = 50;
  int end_ticks = 0;
  int end_delay = 400;
};

}  // namespace team
}  // namespace senseless_soccer
