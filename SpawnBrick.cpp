#include "SpawnBrick.h"
#include "GameWindow.h"
#include "Texture.h"

SpawnBrick::SpawnBrick(float _x, float _y, int _health, int _layer) : Brick(_x, _y, _health, _layer)
{
	texture = Texture::GetTexture("Spawn");
}

vector<Brick::ActionType> SpawnBrick::getActionsOnDestroy()
{
	vector<Brick::ActionType> onDestroy;
	onDestroy.push_back(SpawnBalls);
	return onDestroy;
}


void SpawnBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}