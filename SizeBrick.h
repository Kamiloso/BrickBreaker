#pragma once
#include "Brick.h"
class SizeBrick : public Brick
{
public:
	SizeBrick(float _x, float _y, int _health = 1, int _layer = 10, bool _mode = true);
	vector<ActionType> getActionsOnDestroy() override;
	void draw(GameWindow* game_window) override;
private:
	sf::Texture* texture = nullptr;
	bool mode;
};


