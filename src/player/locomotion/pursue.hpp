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
#include "locomotion.hpp"
#include <gamelib2/math/vector.hpp>

using namespace gamelib2;
namespace senseless_soccer {

class Player;
// pursue locomption follows a moving target
class Pursue : public Locomotion {
public:
    Pursue(Player *p);
    virtual ~Pursue() override = default;
    virtual void start() override;
    virtual void update(float _dt) override;
    virtual void stop() override;
    virtual bool finished() override;

    void init(const Vector3 &static_target,
                          const Vector3 *dynamic_target = nullptr) override;

private:
    Vector3 *target = nullptr;
};

} // namespace senseless_soccer
