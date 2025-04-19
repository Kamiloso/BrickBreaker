#include "CircleCollider.h"

CircleCollider::CircleCollider(float _x, float _y, float _r, Brick* _brick) :
	Collider(_x, _y, _brick), r(_r) {}

float CircleCollider::getTimeToCollision(Ball* ball)
{
	return -1.0f;
}

void CircleCollider::bounceBall(Ball* ball)
{
	return;
}
