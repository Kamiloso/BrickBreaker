#pragma once
#include "Brick.h"


class UnbreakableBrick : public Brick
{
public:
	UnbreakableBrick(float _x, float _y, int _health = 4, int _layer = 10);
	bool unbreakable() override { return true; };
	void draw(GameWindow* game_window) override;
private:
	sf::Texture* texture = nullptr;
};

