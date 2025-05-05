#include "SizeBrick.h"
#include "GameWindow.h"
#include "Texture.h"
#include "Plate.h"

SizeBrick::SizeBrick(float _x, float _y, bool _mode, const Plate* _plate, int _layer) : Brick(_x, _y, 1, _layer), mode(_mode), plate(_plate)
{
	if (mode) {
		texture = Texture::GetTexture("SizeUp");
		texture2 = Texture::GetTexture("SizeUp2");
	}
	else {
		texture = Texture::GetTexture("SizeDown");
		texture2 = Texture::GetTexture("SizeDown2");
	}
	color = COL::plateParticles;
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
	if (plate == nullptr || !plate->isReversed()) {
		game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
		color = COL::plateParticles;
	}
	else {
		game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture2);
		color = COL::reverseParticles;
	}
}
