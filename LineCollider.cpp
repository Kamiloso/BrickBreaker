#include "LineCollider.h"
#include "Ball.h"

LineCollider::LineCollider(float _x1, float _y1, float _x2, float _y2, Side _side, Brick* _brick)
	: Collider(_brick), x1(_x1), y1(_y1), x2(_x2), y2(_y2), side(_side)
{
	if (side == Up || side == Down)
		y2 = y1;

	if (side == Left || side == Right)
		x2 = x1;
}

float LineCollider::getTimeToCollision(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();

	if (side == Up || side == Down)
	{
		if (b_vel[1] == 0.0f)
			return -1.0f; // perpendicular movement

		float h = b_pos[1] - y1;
		if ((h >= 0.0f && side != Down) || (h <= 0.0f && side != Up))
			return -1.0f; // wrong side of a collider

		float time = -h / b_vel[1];

		float x_final_pos = b_pos[0] + time * b_vel[0];
		if (x_final_pos < x1 || x_final_pos > x2)
			return -1.0f; // will miss collider

		return time > 0.0f ? time : -1.0f;
	}

	if (side == Left || side == Right)
	{
		if (b_vel[0] == 0.0f)
			return -1.0f; // perpendicular movement

		float w = b_pos[0] - x1;
		if ((w >= 0.0f && side != Right) || (w <= 0.0f && side != Left))
			return -1.0f; // wrong side of a collider 

		float time = -w / b_vel[0];

		float y_final_pos = b_pos[1] + time * b_vel[1];
		if (y_final_pos < y1 || y_final_pos > y2)
			return -1.0f; // will miss collider

		return time > 0.0f ? time : -1.0f;
	}
}

void LineCollider::bounceBall(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();

	if (side == Up || side == Down)
	{
		// velocity adjust
		ball->setVelocity(b_vel[0], -b_vel[1]);

		// position adjust (to prevent multiple collisions)
		if (side == Up)
			ball->setPosition(b_pos[0], b_pos[1] - COLLIDER_EPSILON);
		else
			ball->setPosition(b_pos[0], b_pos[1] + COLLIDER_EPSILON);
	}

	if (side == Left || side == Right)
	{
		// velocity adjust
		ball->setVelocity(-b_vel[0], b_vel[1]);

		// position adjust (to prevent multiple collisions)
		if (side == Left)
			ball->setPosition(b_pos[0] - COLLIDER_EPSILON, b_pos[1]);
		else
			ball->setPosition(b_pos[0] + COLLIDER_EPSILON, b_pos[1]);
	}
}
