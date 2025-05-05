#include "NormalBrick.h"
#include "GameWindow.h"
#include "Texture.h"

NormalBrick::NormalBrick(float _x, float _y, int _health, int _layer) : Brick(_x, _y, _health, _layer)
{
	textures[1] = Texture::GetTexture("Health1");
	textures[2] = Texture::GetTexture("Health2");
	textures[3] = Texture::GetTexture("Health3");
	textures[4] = Texture::GetTexture("Health4");
	color = Texture::GetMainColor(textures[1]);
}

void NormalBrick::draw(GameWindow* game_window)
{
	const sf::Texture* texture = (health >= 1 && health <= 4) ? textures[health] : textures[4];
	game_window->drawRectangleWithTexture(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, texture);
}
