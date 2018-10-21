#include	"state.hpp"
#include	"../player.hpp"

namespace	senseless_soccer	{

// -----------------------------------------------------------------------------
// State
// -----------------------------------------------------------------------------
State::State(Player	&context)
  :	player(context)
  ,	sprite(*player.widget)	{
}

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void	State::start()	{
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void	State::update(const	float	_dt)	{
}

// -----------------------------------------------------------------------------
// end
// -----------------------------------------------------------------------------
void	State::end()	{
}

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool	State::finished()	{
				return	false;
}

// -----------------------------------------------------------------------------
// changeToNextState
// -----------------------------------------------------------------------------
void	State::changeToNextState()	{
}

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void	State::handle_input(const	ControllerEvent	&event)	{
				switch	(event.id)	{
								case	Fire:
												if	(event.status	==	Pressed)	{
												}	else	if	(event.status	==	Released)	{
												    if	(player.ball_under_control())	{
																    Vector3	direction	=	player.facing.toVector().normalise();
																				player.kick(direction,	event.param);
																}	else	{
																    if	(Floats::greater_than(Player::ball->position.z,	5))	{
																				    player.jump();
																				}	else	{
																				    player.slide();
																				}
																}
												}
												break;

								case	FireTap:
												if	(player.ball_under_control())	{
												    player.short_pass();
												}	else	{
												    if	(Floats::greater_than(Player::ball->position.z,	5))	{
																    player.jump();
																}	else	{
																    player.slide();
																}
												}
												break;

								case	DPadLeft:
												if	(event.status	==	Pressed)	{
												    player.velocity.x	=	-1;
												}	else	{
												    if	(Floats::equal(player.velocity.x,	-1))	{
																    player.velocity.x	=	0;
																}
												}
												break;

								case	DPadRight:
												if	(event.status	==	Pressed)	{
												    player.velocity.x	=	1;
												}	else	{
												    if	(Floats::equal(player.velocity.x,	1))	{
																    player.velocity.x	=	0;
																}
												}
												break;

								case	DPadUp:
												if	(event.status	==	Pressed)	{
												    player.velocity.y	=	-1;
												}	else	{
												    if	(Floats::equal(player.velocity.y,	-1))	{
																    player.velocity.y	=	0;
																}
												}
												break;

								case	DPadDown:
												if	(event.status	==	Pressed)	{
												    player.velocity.y	=	1;
												}	else	{
												    if	(Floats::equal(player.velocity.y,	1))	{
																    player.velocity.y	=	0;
																}
												}
												break;

								case	NoEvent:
												break;
				}
}

// -----------------------------------------------------------------------------
// on_input_handover
// -----------------------------------------------------------------------------
void	State::on_controller_handover()	{

				if	(player.controller->input.states[Up])	{
				    player.velocity.y	=	-1;
				}

				if	(player.controller->input.states[Down])	{
				    player.velocity.y	=	1;
				}

				if	(player.controller->input.states[Left])	{
				    player.velocity.x	=	-1;
				}

				if	(player.controller->input.states[Right])	{
				    player.velocity.x	=	1;
				}
}

}	// namespace senseless_soccer
