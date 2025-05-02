#pragma once
#include "Brick.h"

class SpawnBrick : public Brick
{
public:
	SpawnBrick(float _x, float _y, int _layer = 10);
	vector<ActionType> getActionsOnDestroy() override { return { SpawnBalls }; }
	void draw(GameWindow* game_window) override;

private:
	sf::Texture* texture = nullptr;
};
