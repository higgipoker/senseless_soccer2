#include "metrics.hpp"

namespace senseless_soccer {

static const float cm_to_px = 0.2f;

// -----------------------------------------------------------------------------
// MetersToPixels
// -----------------------------------------------------------------------------
int Metrics::MetersToPixels(float meters) {
  return static_cast<int>(meters * 100 * cm_to_px);
}

// -----------------------------------------------------------------------------
// MetersToPixels
// -----------------------------------------------------------------------------
gamelib2::Vector3 Metrics::MetersToPixels(gamelib2::Vector3 v) {
  return gamelib2::Vector3(v.x * 100 * cm_to_px, v.y * 100 * cm_to_px,
                           v.z * 100 * cm_to_px);
}

// -----------------------------------------------------------------------------
// PixelsToMeters
// -----------------------------------------------------------------------------
float Metrics::PixelsToMeters(float pixels) { return pixels / cm_to_px / 100; }

// -----------------------------------------------------------------------------
// YardsToMeters
// -----------------------------------------------------------------------------
float Metrics::YardsToMeters(float yards) { return yards * 0.914f; }

// -----------------------------------------------------------------------------
// YardsToPixels
// -----------------------------------------------------------------------------
int Metrics::YardsToPixels(float yards) {
  return MetersToPixels(YardsToMeters(yards));
}

}  // namespace senseless_soccer
