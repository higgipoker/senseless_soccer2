#include	"pitch.hpp"
#include	"../metrics/metrics.hpp"

#include	<gamelib2/widgets/widget.hpp>
namespace	senseless_soccer	{

// -----------------------------------------------------------------------------
// Pitch
// -----------------------------------------------------------------------------
Pitch::Pitch(std::string	in_name)
  :	gamelib2::Entity(std::move(in_name))	{

				// det up a default pitch size
				dimensions.bounds.left	=	10;
				dimensions.bounds.top	=	10;
				dimensions.bounds.width	=	Metrics::MetersToPixels(69);
				dimensions.bounds.height	=	Metrics::MetersToPixels(105);
}

// -----------------------------------------------------------------------------
// ~Ball
// -----------------------------------------------------------------------------
Pitch::~Pitch()	=	default;

// -----------------------------------------------------------------------------
// on_moved
// -----------------------------------------------------------------------------
void	Pitch::onDragged(const	gamelib2::Vector3	&diff)	{
				Entity::onDragged(diff);
				if	(widget)	{
				    widget->move(diff.x,	diff.y);
				}
}
}	// namespace senseless_soccer
