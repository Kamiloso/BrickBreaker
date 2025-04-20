#pragma once

class Ball;
class Brick;

static constexpr float COLLIDER_EPSILON = 0.01f; // by how much will position additionally change during bouncing

class Collider
{
public:
	Collider(Brick* _brick = nullptr);
	Brick* getBrick(); // returns attached brick pointer or nullptr if there is none
	virtual float getTimeToCollision(Ball* ball) = 0; // returns -1.0f if no collision
	virtual void bounceBall(Ball* ball) = 0; // bounces ball velocity and slightly corrects its position to prevent multiple bounces
	virtual ~Collider() {};

private:
	Brick* brick;
};
