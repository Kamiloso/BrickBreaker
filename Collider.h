#pragma once

class Ball;
class Brick;

constexpr float NO_COLLISION = -1.0f; // this float in collisions generally means, that it can't happen
constexpr float COLLIDER_EPSILON = 0.01f; // by how much will position additionally change during bouncing
constexpr float RECOMMENDED_MIN_ANGLE = 20.0f; // minimal angle which is not considered to be paralell to plate

class Collider
{
public:
	Collider(Brick* _brick = nullptr);
	Brick* getBrick(); // returns attached brick pointer or nullptr if there is none
	virtual float getTimeToCollision(Ball* ball) = 0; // returns -1.0f if no collision
	virtual void bounceBall(Ball* ball) = 0; // bounces ball velocity and slightly corrects its position to prevent multiple bounces
	void pretendBounceBall(Ball* ball); // should be used when colliding and not bouncing
	virtual ~Collider() {};

private:
	Brick* brick;
};
