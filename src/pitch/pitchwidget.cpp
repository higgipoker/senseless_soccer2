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
#include	"pitchwidget.hpp"
#include	"pitch.hpp"
#include	<SFML/Graphics.hpp>

namespace	senseless_soccer	{

// -----------------------------------------------------------------------------
//	PitchWidget
// -----------------------------------------------------------------------------
PitchWidget::PitchWidget(const	std::string	&in_file)
  :	TiledScrollingBackground(in_file)	{
}

// -----------------------------------------------------------------------------
//	render
// -----------------------------------------------------------------------------
void	PitchWidget::render(sf::RenderTarget	&target)	{
				// render the tiled background
				TiledScrollingBackground::render(target);

				// draw the pitch lines
				int	offset	=	250;
				Pitch	&pitch	=	static_cast<Pitch	&>(*entity);
				float	line_width	=	2.5f;

				// north horizontal
				sf::RectangleShape	line(
				  sf::Vector2f(pitch.dimensions.bounds.width,	line_width));
				line.move(offset,	offset);
				target.draw(line);

				// east vertical
				line.move(pitch.dimensions.bounds.width,	0);
				line.setSize(sf::Vector2f(pitch.dimensions.bounds.height,	line_width));
				line.rotate(90);
				target.draw(line);

				// south horizontal
				line.move(0,	pitch.dimensions.bounds.height);
				line.setSize(sf::Vector2f(pitch.dimensions.bounds.width,	line_width));
				line.rotate(90);
				target.draw(line);

				// west vertical
				line.move(-pitch.dimensions.bounds.width,	0);
				line.setSize(sf::Vector2f(pitch.dimensions.bounds.height,	line_width));
				line.rotate(90);
				target.draw(line);
}
}	// namespace senseless_soccer
