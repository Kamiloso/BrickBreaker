#include "Brick.h"

Brick::Brick(float _x, float _y, int _layer)
	:Rectangle(_x, _y, BRICK_WX, BRICK_WY, 2, sf::Color::Magenta, sf::Color::Yellow, _layer) {}
