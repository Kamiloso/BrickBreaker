#include "PlateCollider.h"
#include "Ball.h"

#include <iostream>

PlateCollider::PlateCollider(float _y0, float _x1, float _x2)
	: Collider(nullptr), y0(_y0), x1(_x1), x2(_x2) {}

float PlateCollider::getTimeToCollision(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();

	if (b_vel[1] <= 0.0f)
		return NO_COLLISION; // movement up

	float h = b_pos[1] - y0;
	if (h > 0.0f) h = 0.0f; // if under plate, pretend to be on it
	float time = -h / b_vel[1];

	float x_final_pos = b_pos[0] + time * b_vel[0];
	if (x_final_pos < x1 || x_final_pos > x2)
		return NO_COLLISION; // will miss collider

	return time >= 0.0f ? time : NO_COLLISION;
}

void PlateCollider::bounceBall(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();
	float b_vel_magnitude = ball->getVelocityMagnitude();

	// direction choose
	constexpr float MAX_BALL_DEVIATION = 60.0f;
	float x_center = (x1 + x2) / 2;
	float half_width = x2 - x_center;
	float center_deviation = (b_pos[0] - x_center) / half_width;
	if (b_pos[1] > y0 + COLLIDER_EPSILON)
	{
		// after-life bounce
		center_deviation = center_deviation != 0.0f ? abs(center_deviation) / center_deviation : 0.0f;
	}
	float angle_new = center_deviation * MAX_BALL_DEVIATION;

	// velocity adjust
	ball->setVelocityByAngle(270.0f + angle_new, b_vel_magnitude);
	float sign = b_vel[0] != 0 ? abs(b_vel[0]) / b_vel[0] : 0.0f;

	// position adjust (to prevent multiple collisions)
	ball->setPosition(b_pos[0] - sign * COLLIDER_EPSILON, b_pos[1] - COLLIDER_EPSILON);
}
