#include "MovementBrick.h"
#include "GameWindow.h"
#include "Texture.h"
MovementBrick::MovementBrick(float _x, float _y, bool _mode, int _layer) : Brick(_x, _y, 0, _layer), mode(_mode)
{
	if (mode)
		texture = Texture::GetTexture("SpeedUp");
	else
		texture = Texture::GetTexture("SlowDown");
}

vector<Brick::ActionType> MovementBrick::getActionsOnBounce()
{
	if (mode)
		return { SpeedUp };
	else
		return { SlowDown };
}

void MovementBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}

