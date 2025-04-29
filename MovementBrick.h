#pragma once
#include "Brick.h"
class MovementBrick : public Brick
{
public:
	MovementBrick(float _x, float _y, int _health = 4, int _layer = 10,bool _mode = true);
	vector<ActionType> getActionsOnDestroy() override;
	void draw(GameWindow* game_window) override;
private:
	sf::Texture* texture = nullptr;
	bool mode;
};

