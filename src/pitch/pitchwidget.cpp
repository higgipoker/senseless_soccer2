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
#include	"../metrics/metrics.hpp"
#include	<gamelib2/graphics/primitives.hpp>
#include	<SFML/Graphics.hpp>

namespace	senseless_soccer	{

// -----------------------------------------------------------------------------
//	PitchWidget
// -----------------------------------------------------------------------------
PitchWidget::PitchWidget(const	std::string	&in_file,	Camera	&c)
  :	TiledScrollingBackground(in_file,	c)	{
}

// -----------------------------------------------------------------------------
//	render
// -----------------------------------------------------------------------------
void	PitchWidget::render(sf::RenderTarget	&target)	{
				// render the tiled background
				TiledScrollingBackground::render(target);

				// draw the pitch lines
				// todo gather into one draw list
				Pitch	&pitch	=	static_cast<Pitch	&>(*entity);
				float	line_width	=	2.5f;

				// north horizontal
				sf::RectangleShape	line(
				  sf::Vector2f(pitch.dimensions.bounds.width,	line_width));
				line.setPosition(pitch.dimensions.bounds.left,	pitch.dimensions.bounds.top);
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

				// center line
				line.move(0,	-pitch.dimensions.bounds.height	/	2);
				line.setSize(sf::Vector2f(pitch.dimensions.bounds.width,	line_width));
				line.rotate(90);
				target.draw(line);

				// center circle
				sf::CircleShape	circle(pitch.dimensions.center_circle_radius);
				circle.setPointCount(50);
				circle.setFillColor(sf::Color(0,	0,	0,	0));
				circle.setOutlineThickness(2.5);
				circle.setOutlineColor(sf::Color(255,	255,	255,	255));
				circle.setPosition(
				  pitch.dimensions.center.left	-	pitch.dimensions.center_circle_radius,
				  pitch.dimensions.center.top	-	pitch.dimensions.center_circle_radius);
				target.draw(circle);

				// north 6 yard box
				// east vertical
				line.setPosition(sf::Vector2f(pitch.dimensions.north_6.left	+
				                                pitch.dimensions.north_6.width,
				                              pitch.dimensions.north_6.top));
				line.setSize(sf::Vector2f(pitch.dimensions.north_6.height,	line_width));
				line.rotate(90);
				target.draw(line);

				// south horizontal
				line.move(-(pitch.dimensions.north_6.width),
				          pitch.dimensions.north_6.height);
				line.setSize(sf::Vector2f(pitch.dimensions.north_6.width,	line_width));
				line.rotate(-90);
				target.draw(line);

				// west vertical
				line.setSize(sf::Vector2f(pitch.dimensions.north_6.height,	line_width));
				line.rotate(-90);
				target.draw(line);

				// north 18 yard box
				// east vertical
				line.setRotation(0);
				line.setPosition(sf::Vector2f(pitch.dimensions.north_18.left	+
				                                pitch.dimensions.north_18.width,
				                              pitch.dimensions.north_18.top));
				line.setSize(sf::Vector2f(pitch.dimensions.north_18.height,	line_width));
				line.rotate(90);
				target.draw(line);

				// south horizontal
				line.move(-(pitch.dimensions.north_18.width),
				          pitch.dimensions.north_18.height);
				line.setSize(sf::Vector2f(pitch.dimensions.north_18.width,	line_width));
				line.rotate(-90);
				target.draw(line);

				// west vertical
				line.setSize(sf::Vector2f(pitch.dimensions.north_18.height,	line_width));
				line.rotate(-90);
				target.draw(line);

				// south 6 yard box
				// east vertical
				line.setRotation(0);
				line.setPosition(sf::Vector2f(pitch.dimensions.south_6.left	+
				                                pitch.dimensions.south_6.width,
				                              pitch.dimensions.south_6.top));
				line.setSize(sf::Vector2f(pitch.dimensions.south_6.height,	line_width));
				line.rotate(90);
				target.draw(line);

				// south horizontal
				line.move(-(pitch.dimensions.south_6.width),	0);
				line.setSize(sf::Vector2f(pitch.dimensions.south_6.width,	line_width));
				line.rotate(-90);
				target.draw(line);

				// west vertical
				line.setSize(sf::Vector2f(pitch.dimensions.south_6.height,	line_width));
				line.rotate(90);
				target.draw(line);

				// south 18 yard box
				// east vertical
				line.setRotation(0);
				line.setPosition(sf::Vector2f(pitch.dimensions.south_18.left	+
				                                pitch.dimensions.south_18.width,
				                              pitch.dimensions.south_18.top));
				line.setSize(sf::Vector2f(pitch.dimensions.south_18.height,	line_width));
				line.rotate(90);
				target.draw(line);

				// south horizontal
				line.move(-(pitch.dimensions.south_18.width),	0);
				line.setSize(sf::Vector2f(pitch.dimensions.south_18.width,	line_width));
				line.rotate(-90);
				target.draw(line);

				// west vertical
				line.setSize(sf::Vector2f(pitch.dimensions.south_18.height,	line_width));
				line.rotate(90);
				target.draw(line);

				//
				// arc north
				//
				Primitives::arc(
				  target,	pitch.dimensions.bounds.left	+	pitch.dimensions.bounds.width	/	2,
				  pitch.dimensions.north_18.top	+	pitch.dimensions.north_18.height	-	99,
				  Metrics::MetersToPixels(9.15f),	33,	148,	100,	3);

				//
				// arc south
				//
				Primitives::arc(
				  target,	pitch.dimensions.bounds.left	+	pitch.dimensions.bounds.width	/	2,
				  pitch.dimensions.south_18.top	+	99,	Metrics::MetersToPixels(9.15f),	213,
				  329,	100,	3);

				Widget::render(target);
}
}	// namespace senseless_soccer
