#include "MovementBrick.h"
#include "GameWindow.h"
#include "Texture.h"
MovementBrick::MovementBrick(float _x, float _y, int _health, int _layer,bool _mode) : Brick(_x, _y, _health, _layer), mode(_mode)
{
	if (mode)
	{
		texture = Texture::GetTexture("SpeedUp");
	}
	else
	{
		texture = Texture::GetTexture("SlowDown");
	}
}

vector<Brick::ActionType> MovementBrick::getActionsOnDestroy()
{
	vector<Brick::ActionType> onDestroy;
	if (mode)
	{
		onDestroy.push_back(SpeedUp);
	}
	else
	{
		onDestroy.push_back(SlowDown);
	}
	return onDestroy;
}

void MovementBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}

