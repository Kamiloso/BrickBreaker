#pragma once
#include "Brick.h"

class MovementBrick : public Brick
{
public:
	MovementBrick(float _x, float _y, bool _mode, int _layer = 10);
	bool unbreakable() override { return true; }
	vector<ActionType> getActionsOnBounce() override;
	void draw(GameWindow* game_window) override;

private:
	sf::Texture* texture = nullptr;
	bool mode;
};

