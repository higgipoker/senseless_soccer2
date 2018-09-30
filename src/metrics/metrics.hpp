#pragma once

#include <gamelib2/math/vector.hpp>

namespace senseless_soccer {

class Metrics {
 public:

  /**
   * @brief converts meters to pixels
   * @param meters meters to convert
   */
  static int MetersToPixels(float meters);

  /**
   * @brief converts pixels to meters
   * @param pixels pixels to convert
   */
  static float PixelsToMeters(float pixels);

  /**
   * @brief converts yards to meters
   * @param yards yards to convert
   */
  static float YardsToMeters(float yards);

  /**
   * @brief converts yards to pixels
   * @param yards yards to convert
   */
  static int YardsToPixels(float yards);

  /// trial and error force to pass ball one meter
  static constexpr float force_per_meter = 0.1f;
};

}  // namespace SenselessSoccer
