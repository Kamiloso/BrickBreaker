#pragma once
#include "Brick.h"
class ReverseBrick : public Brick
{
public:
	ReverseBrick(float _x, float _y, int _health = 1, int _layer = 10);
	vector<ActionType> getActionsOnDestroy() override;
	void draw(GameWindow* game_window) override;
private:
	sf::Texture* texture = nullptr;
};

