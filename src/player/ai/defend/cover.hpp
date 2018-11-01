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
#include "../brainstate.hpp"
#include "../../../pitch/pitch.hpp"

#include <gamelib2/utils/grid.hpp>

#include <memory>

namespace senseless_soccer {
class Brain;
namespace ai {
class Cover : public BrainState {
   public:
    Cover(Brain &b);
    virtual ~Cover() override = default;
    virtual void start() override;
    virtual void stop() override;
    virtual bool finished() override;
    virtual void update(float dt) override;

protected:
    int last_sector = -1;
    std::weak_ptr<gamelib2::Grid> grid;
    std::weak_ptr<Pitch> pitch;
};
}  // namespace ai
}  // namespace senseless_soccer
