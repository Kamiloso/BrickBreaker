#include "Brick.h"
#include "GameWindow.h"

Brick::Brick(float _x, float _y, int _health, int _layer) : health(_health),
	Rectangle(_x, _y, BRICK_WX, BRICK_WY, 3, COL::brick, sf::Color::Black, _layer) {}

void Brick::damage(int dmg)
{
	health -= dmg;
}

bool Brick::shouldBreak() const
{
	return health <= 0;
}

void Brick::draw(GameWindow* game_window)
{
	// Similar to drawing rectangle, but smaller (will change in the future)
	const float SMALLER_BY = 2.0f;
	game_window->drawRectangle(x, y, wx - SMALLER_BY, wy - SMALLER_BY, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2 - SMALLER_BY, wy - bold * 2 - SMALLER_BY, color);
}

vector<float> Brick::getBrickPositionByCoordinates(int x, int y)
{
	const float COLUMN_0_X = CX - (BRICKS_X - 1) * BRICK_WX / 2;
	const float LAYER_0_Y = 50.0f;
	return {
		COLUMN_0_X + x * BRICK_WX,
		LAYER_0_Y + y * BRICK_WY
	};
}
