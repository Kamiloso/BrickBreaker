#pragma once

class Ball;
class Brick;

class Collider
{
public:
	Collider(float _x, float _y, Brick* _brick);
	virtual float getTimeToCollision(Ball* ball) = 0; // returns -1.0f if no collision
	virtual void bounceBall(Ball* ball) = 0; // bounces ball velocity without affecting its position
	virtual ~Collider() {};

private:
	float x;
	float y;
	Brick* brick;
};

