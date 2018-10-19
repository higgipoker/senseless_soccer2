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
#include <gamelib2/math/vector.hpp>
#include <string>
using namespace gamelib2;
namespace senseless_soccer {

class Player;
class Locomotion {
public:
    Locomotion(Player *p);
    virtual ~Locomotion() = default;
    void init(const Vector3 &static_target,
              const Vector3 *dynamic_target = nullptr);
    virtual void start();
    virtual void update(float _dt);
    virtual void stop();
    virtual bool finished() = 0;
    std::string name;

protected:
    Player *player = nullptr;
    bool state_over = false;
    Vector3 destination;
    Vector3 static_target;
    const Vector3 *dynamic_target = nullptr;
    bool destination_reached = false;
};
} // namespace senseless_soccer