#include "MovementBrick.h"
#include "GameWindow.h"
#include "Texture.h"
MovementBrick::MovementBrick(float _x, float _y, bool _mode, int _layer) : Brick(_x, _y, 0, _layer), mode(_mode)
{
	if (mode) {
		texture = Texture::GetTexture("SpeedUp");
		texture2 = Texture::GetTexture("SpeedUp2");
	}
	else {
		texture = Texture::GetTexture("SlowDown");
		texture2 = Texture::GetTexture("SlowDown2");
	}
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
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, visual_counter <= 0.0f ? texture : texture2);
}

void MovementBrick::specialMovementUpdate(float delta_time)
{
	visual_counter -= delta_time;
	if (visual_counter < 0.0f)
		visual_counter = 0.0f;
}

void MovementBrick::activateVisual()
{
	constexpr float VISUAL_TIME = 0.2f;
	visual_counter = VISUAL_TIME;
}
