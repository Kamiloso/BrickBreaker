#include "SizeBrick.h"
#include "GameWindow.h"
#include "Texture.h"

SizeBrick::SizeBrick(float _x, float _y, bool _mode, int _layer) : Brick(_x, _y, 1, _layer), mode(_mode)
{
	if (mode)
		texture = Texture::GetTexture("SizeUp");
	else
		texture = Texture::GetTexture("SizeDown");
}

vector<Brick::ActionType> SizeBrick::getActionsOnDestroy()
{
	if (mode)
		return { WiderPlate };
	else
		return { ShorterPlate };
}

void SizeBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}
