#pragma once

#include <gamelib2/math/vector.hpp>
#include <vector>

namespace senseless_soccer {

class Metrics {
public:
    // converts meters to pixels
    static int MetersToPixels(float meters);

    // converts pixels to meters
    static float PixelsToMeters(float pixels);

    // converts yards to meters
    static float YardsToMeters(float yards);

    // converts yards to pixels
    static int YardsToPixels(float yards);

    // trial and error force to pass ball one meter
    static constexpr float force_per_meter = 0.1f;
};

} // namespace senseless_soccer
