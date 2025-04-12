#include "Circle.h"
#include "GameWindow.h"

Circle::Circle(float _x, float _y, float _r, float _bold, sf::Color _color, sf::Color _color_bold, int _layer)
	: SceneObject(_x, _y, _layer), r(_r),
	bold(_bold), color(_color), color_bold(_color_bold) {}

void Circle::draw(GameWindow* game_window)
{
	if (bold > 0.0f) game_window->drawCircle(x, y, r, color_bold);
	game_window->drawCircle(x, y, r - bold, color);
}
