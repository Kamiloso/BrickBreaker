#include "Rectangle.h"
#include "GameWindow.h"

Rectangle::Rectangle(float _x, float _y, float _wx, float _wy, float _bold, sf::Color _color, sf::Color _color_bold, int _layer)
	: SceneObject(_x, _y, _layer), wx(_wx), wy(_wy),
	bold(_bold), color(_color), color_bold(_color_bold) {}

void Rectangle::draw(GameWindow* game_window)
{
	if(bold > 0.0f) game_window->drawRectangle(x, y, wx, wy, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2, wy - bold * 2, color);
}

vector<float> Rectangle::getScale() const
{
	return vector<float>{wx, wy};
}
