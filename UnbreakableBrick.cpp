#include "UnbreakableBrick.h"
#include "GameWindow.h"
#include "Texture.h"
UnbreakableBrick::UnbreakableBrick(float _x, float _y, int _health, int _layer) : Brick(_x, _y, _health, _layer)
{
	texture = Texture::GetTexture("Unbreakable");
}

void UnbreakableBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}

