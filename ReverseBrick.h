#pragma once
#include "Brick.h"

class ReverseBrick : public Brick
{
public:
	ReverseBrick(float _x, float _y, int _layer = 10);
	vector<ActionType> getActionsOnDestroy() override { return { ReverseControl }; }
	void draw(GameWindow* game_window) override;

private:
	const sf::Texture* texture = nullptr;
};

