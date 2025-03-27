#include "Rectangle.h"
#include "GameWindow.h"

Rectangle::Rectangle(float _x, float _y, float _wx, float _wy, float _bold, sf::Color _color, sf::Color _color_bold)
	: SceneObject(_x, _y), wx(_wx), wy(_wy), bold(_bold), color(_color), color_bold(_color_bold)
{
	if (bold * 2 > wx || bold * 2 > wy)
		bold = 0.0f;
}

void Rectangle::draw(GameWindow* game_window)
{
	game_window->drawRectangle(x, y, wx, wy, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2, wy - bold * 2, color);
}
