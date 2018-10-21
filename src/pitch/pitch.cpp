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
				dimensions.bounds.left	=	250;
				dimensions.bounds.top	=	250;
				dimensions.bounds.width	=	Metrics::MetersToPixels(69);
				dimensions.bounds.height	=	Metrics::MetersToPixels(105);
				dimensions.center_circle_radius	=	Metrics::MetersToPixels(9.15f);

				// north 6 yard
				dimensions.north_6.width	=	Metrics::MetersToPixels(18.32f);
				dimensions.north_6.height	=	Metrics::MetersToPixels(5.5f);
				dimensions.north_6.left	=	dimensions.bounds.left	+
				  (dimensions.bounds.width	/	2)	-	(dimensions.north_6.width	/	2);
				dimensions.north_6.top	=	dimensions.bounds.top;

				// north 18 yard
				dimensions.north_18.width	=	Metrics::MetersToPixels(40.32f);
				dimensions.north_18.height	=	Metrics::MetersToPixels(16.5f);
				dimensions.north_18.left	=
				  (dimensions.bounds.left	+	dimensions.bounds.width	/	2)	-
				  (dimensions.north_18.width	/	2);
				dimensions.north_18.top	=	dimensions.bounds.top;

				// south 6
				dimensions.south_6	=	dimensions.north_6;
				dimensions.south_6.top	=	dimensions.bounds.top	+	dimensions.bounds.height	-
				  dimensions.south_6.height;

				// south 18
				dimensions.south_18	=	dimensions.north_18;
				dimensions.south_18.top	=	dimensions.bounds.top	+	dimensions.bounds.height	-
				  dimensions.south_18.height;

				// center point
				dimensions.center.left	=
				  dimensions.bounds.left	+	(dimensions.bounds.width	/	2);
				dimensions.center.top	=
				  dimensions.bounds.top	+	(dimensions.bounds.height	/	2);

				// goals
				dimensions.goal_north.width	=	Metrics::MetersToPixels(7.32f);
				dimensions.goal_north.height	=	Metrics::MetersToPixels(2.44f);
				dimensions.goal_north.left	=
				  (dimensions.bounds.left	+	dimensions.bounds.width	/	2)	-
				  (dimensions.goal_north.width	/	2)	+	76;
				dimensions.goal_north.top	=	dimensions.bounds.top;

				dimensions.goal_south	=	dimensions.goal_north;
				dimensions.goal_south.top	+=	dimensions.bounds.height;
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
