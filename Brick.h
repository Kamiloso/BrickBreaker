#pragma once
#include "Rectangle.h"
#include "common.h"

class Brick : public Rectangle
{
public:
	Brick(float _x, float _y, int _health = 4, int _layer = 10);
	void damage(int dmg = 1); // damages the brick
	bool shouldBreak() const; // should scene break this brick in the following sceneUpdate?

	void draw(GameWindow* game_window) override;

	static vector<float> getBrickPositionByCoordinates(int x, int y); // returns brick positions based on slot coordinates

protected:
	int health;
};
