#include "SizeBrick.h"
#include "GameWindow.h"
#include "Texture.h"
SizeBrick::SizeBrick(float _x, float _y, int _health, int _layer, bool _mode) : Brick(_x, _y, _health, _layer), mode(_mode)
{
	if (mode)
	{
		texture = Texture::GetTexture("SizeUp");
	}
	else
	{
		texture = Texture::GetTexture("SizeDown");
	}

}

vector<Brick::ActionType> SizeBrick::getActionsOnDestroy()
{
	vector<Brick::ActionType> onDestroy;
	if (mode)
	{
		onDestroy.push_back(WiderPlate);
	}
	else
	{
		onDestroy.push_back(ShorterPlate);
	}
	return onDestroy;
}

void SizeBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}

