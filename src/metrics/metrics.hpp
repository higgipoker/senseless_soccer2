#pragma	once

#include	<gamelib2/math/vector.hpp>
#include	<vector>

namespace	senseless_soccer	{

class	Metrics	{
public:
				// converts meters to pixels
				static	int	MetersToPixels(float	meters);

				// converts pixels to meters
				static	float	PixelsToMeters(float	pixels);

				// converts yards to meters
				static	float	YardsToMeters(float	yards);

				// converts yards to pixels
				static	int	YardsToPixels(float	yards);

				// trial and error force to pass ball one meter
				static	constexpr	float	force_per_meter	=	0.1f;
};

/// dictated by the graphics style
const	float	Y_OFFSET_DUE_TO_HEIGHT	=	0.5f;
const	float	CM_PER_PIXEL	=	7.6f;
static	const	float	CAMERA_HEIGHT	=	Metrics::MetersToPixels(4);

}	// namespace senseless_soccer
