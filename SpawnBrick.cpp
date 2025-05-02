#include "SpawnBrick.h"
#include "GameWindow.h"
#include "Texture.h"

SpawnBrick::SpawnBrick(float _x, float _y, int _layer) : Brick(_x, _y, 1, _layer)
{
	texture = Texture::GetTexture("Spawn");
}

void SpawnBrick::draw(GameWindow* game_window)
{
	// Generate default image
	const sf::Color brick_bg(180, 240, 180);
	game_window->drawRectangle(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, color_bold);
	game_window->drawRectangle(x, y, wx - BRICK_SMALLER_BY - bold * 2, wy - BRICK_SMALLER_BY - bold * 2, brick_bg);
	for (int i = -1; i <= 1; i++)
	{
		const float circle_radius = 12.0f - (i != 0) * 2.0f;
		const float circle_offset = 28.0f;
		game_window->drawCircle(x + i * circle_offset, y, circle_radius, sf::Color::Black);
		game_window->drawCircle(x + i * circle_offset, y, circle_radius - 3.0f, COL::ball);
	}
	
	// Overwrite with texture (perfectly transparent by default)
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}