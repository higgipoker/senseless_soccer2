#include	"sliding.hpp"
#include	"running.hpp"
#include	"../player.hpp"

namespace	senseless_soccer	{

// -----------------------------------------------------------------------------
// Stand
// -----------------------------------------------------------------------------
Sliding::Sliding(Player	&context)
  :	State(context)	{
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void	Sliding::start()	{
				if	(player.widget)	{
				    player.widget->startAnimation(
								  Player::slide_animation_map[player.facing.direction]);
				}
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void	Sliding::update(const	float	_dt)	{
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void	Sliding::end()	{
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool	Sliding::finished()	{
				return	player.widget->currentAnimation()->finished();
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void	Sliding::changeToNextState()	{
				player.sliding	=	false;
				player.change_state(PlayerState::Stand);
}
}	// namespace senseless_soccer
