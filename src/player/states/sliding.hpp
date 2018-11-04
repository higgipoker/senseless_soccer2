#pragma	once
#include	<gamelib2/types.hpp>
#include	<gamelib2/widgets/sprite.hpp>

#include	"state.hpp"

namespace	senseless_soccer	{

class	Sliding	:	public	State	{
public:
				// specific constructor to get player pointer
				Sliding(Player	&context);

				// state started
				void	start()	override;

				// main update
				void	update(const	float	dt)	override;

				// state over
				void	end()	override;

				// check for end state
				bool	finished()	override;

				// change to next state
				void	changeToNextState()	override;

				// handle input
				void	handle_input(const	ControllerEvent	&event)	override;

private:
				// how quickly the player gets up after the slide
				unsigned	int	recover_frames	=	60;

				// in the recovery (getting up) phase
				bool	getting_up	=	false;
};

}	// namespace senseless_soccer
