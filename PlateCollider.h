#pragma once
#include "Collider.h"

class PlateCollider : public Collider
{
public:
	PlateCollider(float _y0, float _x1, float _x2);
	float getTimeToCollision(Ball* ball) override;
	void bounceBall(Ball* ball) override;

private:
	float y0; // height
	float x1, x2; // borders
};
