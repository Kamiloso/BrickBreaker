#include "SpawnBrick.h"
#include "GameWindow.h"
#include "Texture.h"

SpawnBrick::SpawnBrick(float _x, float _y, int _layer) : Brick(_x, _y, 1, _layer)
{
	texture = Texture::GetTexture("Spawn");
	color = COL::ball;
}

void SpawnBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}