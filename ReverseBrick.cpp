#include "ReverseBrick.h"
#include "GameWindow.h"
#include "Texture.h"

ReverseBrick::ReverseBrick(float _x, float _y, int _layer) : Brick(_x, _y, 1, _layer)
{
	texture = Texture::GetTexture("Reverse");
	color = COL::reverseParticles;
	sound = "reverse";
}

void ReverseBrick::draw(GameWindow* game_window)
{
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}

