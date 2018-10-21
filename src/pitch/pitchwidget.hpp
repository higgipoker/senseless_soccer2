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
#pragma	once
#include	<gamelib2/widgets/tiledscrollingbackground.hpp>
#include	<gamelib2/camera/camera.hpp>
#include	<gamelib2/utils/files.hpp>
#include	<gamelib2/widgets/sprite.hpp>

using	namespace	gamelib2;
namespace	senseless_soccer	{
class	PitchWidget	:	public	TiledScrollingBackground	{
public:
				PitchWidget(const	std::string	&in_file,	Camera	&c);
				void	render(sf::RenderTarget	&target)	override;

private:
				std::unique_ptr<Widget>	goal_north	=	std::make_unique<Sprite>(
				  Files::getWorkingDirectory()	+	"/gfx/goal_top_new.png",	1,	1);

				std::unique_ptr<Widget>	goal_south	=	std::make_unique<Sprite>(
				  Files::getWorkingDirectory()	+	"/gfx/goal_bottom_new_persepective.png",	1,
				  1);
};
}	// namespace senseless_soccer
