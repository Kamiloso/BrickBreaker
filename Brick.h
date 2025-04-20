#pragma once
#include "Rectangle.h"
#include "common.h"

#include <string>

class Collider;

constexpr float BRICK_SMALLER_BY = 4.0f; // width of the gap between bricks

class Brick : public Rectangle
{
public:
	Brick(float _x, float _y, int _health = 4, int _layer = 10);
	virtual void damage(int dmg = 1); // damages the brick
	virtual bool shouldBreak() const; // should scene break this brick in the following sceneUpdate?
	vector<Collider*> createNewColliders(bool up, bool down, bool left, bool right); // creates brick colliders on heap and returns vector of them

	void draw(GameWindow* game_window) override;

	static vector<float> getBrickPositionByCoordinates(int x, int y); // returns brick positions based on slot coordinates

protected:
	int health;
};
