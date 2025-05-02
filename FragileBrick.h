#pragma once
#include "Brick.h"
class FragileBrick : public Brick
{
public:
	FragileBrick(float _x, float _y, int _layer = 10);
	bool goesThrough() override { return true; };
	void draw(GameWindow* game_window) override;

private:
	sf::Texture* texture = nullptr;
};

