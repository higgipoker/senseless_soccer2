#pragma	once
#include	<gamelib2/game/entity.hpp>
#include	<SFML/Graphics.hpp>
namespace	senseless_soccer	{

typedef	struct	{

				// pitch lines
				sf::FloatRect	bounds;
				int	center_circle_radius;
				sf::FloatRect	north_6;
				sf::FloatRect	north_18;
				sf::FloatRect	south_6;
				sf::FloatRect	south_18;
				sf::FloatRect	center;

				//	goals
				sf::FloatRect	goal_north;
				sf::FloatRect	goal_south;

}	PitchDimensions;

class	Pitch	:	public	gamelib2::Entity	{
public:
				// construct with an entity name
				Pitch(std::string	in_name);
				virtual	~Pitch();

				// the entity was manually moved
				void	onDragged(const	gamelib2::Vector3	&new_position)	override;

				PitchDimensions	dimensions;

protected:
};

}	// namespace senseless_soccer
