#pragma once
#include "Brick.h"

class NormalBrick : public Brick
{
public:
	NormalBrick(float _x, float _y, int _health = 4, int _layer = 10);
	void draw(GameWindow* game_window) override;

private:
	sf::Texture* textures[5] = {}; // health textures, index 0 is nullptr
};
