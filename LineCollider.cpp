#include "LineCollider.h"

LineCollider::LineCollider(float _x, float _y, float _angle, Brick* _brick) :
	Collider(_x, _y, _brick), angle(_angle) {}

float LineCollider::getTimeToCollision(Ball* ball)
{
	return -1.0f;
}

void LineCollider::bounceBall(Ball* ball)
{
	return;
}
