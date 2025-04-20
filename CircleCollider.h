#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(float _x, float _y, float _r, Brick* _brick = nullptr);
	float getTimeToCollision(Ball* ball) override;
	void bounceBall(Ball* ball) override;

private:
	float x, y; // center position
	float r; // radius
};
