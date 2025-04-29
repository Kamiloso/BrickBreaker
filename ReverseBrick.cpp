#include "ReverseBrick.h"
#include "GameWindow.h"
#include "Texture.h"

ReverseBrick::ReverseBrick(float _x, float _y, int _health, int _layer) : Brick(_x,_y,_health,_layer)
{
	texture = Texture::GetTexture("Reverse");
}

vector<Brick::ActionType> ReverseBrick::getActionsOnDestroy()
{
	vector<Brick::ActionType> onDestroy;
	onDestroy.push_back(ReverseControl);
	return onDestroy;
}


void ReverseBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}

