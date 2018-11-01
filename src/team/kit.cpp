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
#include "kit.hpp"

namespace senseless_soccer {
namespace team {
Kit::Kit() = default;

Kit Kit::Kit::make_standard_red_kit() {
  // graphic is already standard red kit for now
  Kit kit;
  return kit;
}

Kit Kit::Kit::make_standard_blue_kit() {
  Kit kit;

  kit.palette.emplace_back(
      std::make_pair(sf::Color(135, 0, 0), sf::Color(0, 0, 135)));
  kit.palette.emplace_back(
      std::make_pair(sf::Color(175, 0, 0), sf::Color(0, 0, 175)));
  kit.palette.emplace_back(
      std::make_pair(sf::Color(215, 0, 0), sf::Color(0, 0, 215)));
  kit.palette.emplace_back(
      std::make_pair(sf::Color(255, 0, 0), sf::Color(0, 0, 255)));

  return kit;
}

Kit Kit::Kit::make_standard_gk_kit() {
  Kit kit;

  kit.palette.emplace_back(
      std::make_pair(sf::Color(135, 0, 0), sf::Color(0, 135, 0)));
  kit.palette.emplace_back(
      std::make_pair(sf::Color(175, 0, 0), sf::Color(0, 175, 0)));
  kit.palette.emplace_back(
      std::make_pair(sf::Color(215, 0, 0), sf::Color(0, 215, 0)));
  kit.palette.emplace_back(
      std::make_pair(sf::Color(255, 0, 0), sf::Color(0, 255, 0)));

  return kit;
}
}  // namespace team
}  // namespace senseless_soccer
