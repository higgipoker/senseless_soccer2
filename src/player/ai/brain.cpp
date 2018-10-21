/****************************************************************************
	* Copyright (c) 2018 P. Higgins
	*
	* This software is provided 'as-is', without any express or implied
	* warranty. In no event will the authors be held liable for any damages
	* arising from the use of this software.
	*
	* Permission is granted to anyone to use this software for any purpose,
	* including commercial applications, and to alter it and redistribute it
	* freely, subject to the following restrictions:
	*
	* 1. The origin of this software must not be misrepresented; you must not
	*    claim that you wrote the original software. If you use this software
	*    in a product, an acknowledgment in the product documentation would be
	*    appreciated but is not required.
	* 2. Altered source versions must be plainly marked as such, and must not be
	*    misrepresented as being the original software.
	* 3. This notice may not be removed or altered from any source distribution.
	****************************************************************************/
#include	"brain.hpp"
#include	"../player.hpp"

namespace	senseless_soccer	{
namespace	ai	{

// -----------------------------------------------------------------------------
// Brain
// -----------------------------------------------------------------------------
Brain::Brain(Player	&p)
  :	player(p)
  ,	idle(*this)
  ,	dribble(*this)
  ,	receive_pass(*this)
  ,	locomotion(player)	{
				locomotion.startStand();
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void	Brain::update(float	dt)	{
				current_state->update(dt);
				if	(current_state->finished())	{
				    current_state->stop();
								current_state->changeToNextState();
								current_state->start();
				}

				locomotion.update(dt);
}

// -----------------------------------------------------------------------------
// handleMessage
// -----------------------------------------------------------------------------
void	Brain::message(const	std::string	&msg)	{
				if	(msg	==	"receive")	{
				    changeState(State::BrainReceive);
				}	else	if	(msg	==	"dribble")	{
				    locomotion.startStand();
				}
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void	Brain::changeState(const	State	state)	{
				switch	(state)	{
								case	State::BrainIdle:
												current_state->stop();
												current_state	=	&idle;
												current_state->start();
												break;
								case	State::BrainDribble:
												current_state->stop();
												current_state	=	&dribble;
												current_state->start();
												break;

								case	State::BrainPass:
												break;

								case	State::BrainReceive:
												current_state->stop();
												current_state	=	&receive_pass;
												current_state->start();
												break;
				}
}
}	// namespace ai
}	// namespace senseless_soccer
