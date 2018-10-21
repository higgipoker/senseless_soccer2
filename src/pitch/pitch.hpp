#pragma	once
#include	<gamelib2/game/entity.hpp>
#include	<SFML/Graphics.hpp>
namespace	senseless_soccer	{

typedef	struct	{
				sf::Rect<float>	bounds;
				int	center_circle_radius;

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
