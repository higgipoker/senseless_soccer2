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
// PixelsToMeters
// -----------------------------------------------------------------------------
float Metrics::PixelsToMeters(float pixels) {
    return pixels / cm_to_px / 100;
}

// -----------------------------------------------------------------------------
// YardsToMeters
// -----------------------------------------------------------------------------
float Metrics::YardsToMeters(float yards) {
    return yards * 0.914f;
}

// -----------------------------------------------------------------------------
// YardsToPixels
// -----------------------------------------------------------------------------
int Metrics::YardsToPixels(float yards) {
    return MetersToPixels(YardsToMeters(yards));
}

} // namespace senseless_soccer
