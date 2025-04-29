#pragma once
#include "Brick.h"

class SizeBrick : public Brick
{
public:
	SizeBrick(float _x, float _y, bool _mode, int _layer = 10);
	vector<ActionType> getActionsOnDestroy() override;
	void draw(GameWindow* game_window) override;

private:
	sf::Texture* texture = nullptr;
	bool mode;
};
