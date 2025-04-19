#pragma once
#include "Collider.h"

class LineCollider : public Collider
{
public:
	LineCollider(float _x, float _y, float _angle, Brick* _brick); // angle in degrees
	float getTimeToCollision(Ball* ball) override;
	void bounceBall(Ball* ball) override;

private:
	float angle; // angle in degrees
};
