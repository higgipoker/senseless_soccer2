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
#include	"receivepass.hpp"
#include	"../brain.hpp"
#include	"../../player.hpp"

namespace	senseless_soccer	{
namespace	ai	{

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ReceivePass::ReceivePass(Brain	&b)
  :	BrainState(b)	{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void	ReceivePass::start()	{
				//	run towards ball
				brain.locomotion.startPursue(&Player::ball->position);

				//	don't let user run away when input attached
				brain.player.input_suspended	=	true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void	ReceivePass::stop()	{
				brain.player.input_suspended	=	false;
				brain.player.velocity.reset();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool	ReceivePass::finished()	{
				return	brain.player.ball_under_control();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void	ReceivePass::update(float	dt)	{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void	ReceivePass::changeToNextState()	{
				brain.changeState(State::BrainIdle);
}
}	// namespace ai
}	// namespace senseless_soccer
