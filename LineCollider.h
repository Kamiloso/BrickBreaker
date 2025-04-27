#pragma once
#include "Collider.h"

// ----- WARNING -----
// This class supports only vertical and horizontal one-sided colliders

class LineCollider : public Collider
{
public:
	enum Side { Up, Down, Left, Right };

	LineCollider(float _x1, float _y1, float _x2, float _y2, Side _side, Brick* _brick = nullptr);
	float getTimeToCollision(Ball* ball) override;
	void bounceBall(Ball* ball) override;

private:
	float x1, y1; // first point coordinates
	float x2, y2; // second point coordinates
	Side side; // which side of collider is it?

	void preventHorizontalBallMovement(Ball* ball, float min_angle); // prevents ball movement parallel to plate
	void preventVerticalBallMovement(Ball* ball, float min_angle); // prevents ball movement perpandicular to plate
};
