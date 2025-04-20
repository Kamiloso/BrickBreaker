#include "CircleCollider.h"
#include "Ball.h"

#include <cmath>

CircleCollider::CircleCollider(float _x, float _y, float _r, Brick* _brick) :
	Collider(_brick), x(_x), y(_y), r(_r) {}

float CircleCollider::getTimeToCollision(Ball* ball)
{
	return -1.0f;
}

void CircleCollider::bounceBall(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();

	// vector: [center] ---> [ball]
	float rx = b_pos[0] - x;
	float ry = b_pos[1] - y;
	float rv_magnitude = sqrt(rx * rx + ry * ry);

	// normalize vector
	float nx = rx / rv_magnitude;
	float ny = ry / rv_magnitude;

	// dot product b_vel (*) nv
	float dot_product = nx * b_vel[0] + ny * b_vel[1];

	// velocity change (based on ChatGPT's formula)
	ball->setVelocity(
		b_vel[0] - 2 * dot_product * nx,
		b_vel[1] - 2 * dot_product * ny
	);

	// position adjust (to prevent multiple collisions)
	ball->setPosition(
		b_pos[0] + nx * COLLIDER_EPSILON,
		b_pos[1] + ny * COLLIDER_EPSILON
	);
}
