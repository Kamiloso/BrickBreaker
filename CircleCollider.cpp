#include "CircleCollider.h"
#include "Ball.h"

#include <cmath>

CircleCollider::CircleCollider(float _x, float _y, float _r, Brick* _brick) :
	Collider(_brick), x(_x), y(_y), r(_r) {}

float CircleCollider::getTimeToCollision(Ball* ball)
{
	auto b_pos = ball->getPosition();
	auto b_vel = ball->getVelocity();

	float a = b_vel[0] * b_vel[0] + b_vel[1] * b_vel[1];
	float b = 2 * ((b_pos[0] - x) * b_vel[0] + (b_pos[1] - y) * b_vel[1]);
	float c = (b_pos[0] - x) * (b_pos[0] - x) + (b_pos[1] - y) * (b_pos[1] - y) - r * r;
	float delta = b * b - 4 * a * c;

	if (delta < 0.0f)
		return NO_COLLISION; // will not collide
	
	float t1 = (-b - sqrt(delta)) / (2 * a); // only smaller solution
	if (t1 <= 0.0f)
		return NO_COLLISION; // detected past collision

	return t1;
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
