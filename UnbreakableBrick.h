#pragma once
#include "Brick.h"

class UnbreakableBrick : public Brick
{
public:
	UnbreakableBrick(float _x, float _y, int _layer = 10);
	bool unbreakable() const override { return true; };
	void draw(GameWindow* game_window) override;

private:
	const sf::Texture* texture = nullptr;
};

