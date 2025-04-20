#include "Collider.h"
#include "Ball.h"

#include <cmath>

Collider::Collider(Brick* _brick) : brick(_brick) {}

Brick* Collider::getBrick()
{
	return brick;
}

void Collider::pretendBounceBall(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();
	float b_vel_magnitude = ball->getVelocityMagnitude();

	// normalize velocity vector
	float nx = b_vel[0] / b_vel_magnitude;
	float ny = b_vel[1] / b_vel_magnitude;

	ball->setPosition(
		b_pos[0] - nx * COLLIDER_EPSILON,
		b_pos[1] - ny * COLLIDER_EPSILON
	);
}
