#include "Ball.h"
#include "GameWindow.h"
#include "GameScene.h"
#include "Sound.h"
#include "Collider.h"

#include <vector>
#include <cmath>
#include <limits>
#include <iostream>

Ball::Ball(float _x, float _y, float _vx, float _vy, int _layer)
	: Circle(_x, _y, BALL_RADIUS, 3, sf::Color::Green, sf::Color::Black, _layer),
	vx(_vx), vy(_vy) {}

void Ball::step(float time)
{
	x += vx * time;
	y += vy * time;
}

void Ball::setVelocity(float _vx, float _vy)
{
	vx = _vx;
	vy = _vy;
}

void Ball::setVelocityByAngle(float angle, float magnitude)
{
	vx = cos(angle * PI / 180) * magnitude;
	vy = sin(angle * PI / 180) * magnitude;
}

vector<float> Ball::getVelocity() const
{
	return { vx, vy };
}

float Ball::getVelocityAngle() const
{
	return atan2(vy, vx) * 180 / PI;
}

float Ball::getVelocityMagnitude() const
{
	return sqrt(vx * vx + vy * vy);
}

void Ball::resetTime()
{
	time_available = 0.0f;
}

void Ball::changeTime(float time)
{
	time_available += time;
}

float Ball::getTimeAvailable() const
{
	return time_available;
}

void Ball::markToTerminate()
{
	terminate = true;
}

bool Ball::isMarkedAsTerminated() const
{
	return terminate;
}

Collider* Ball::bestFitCollider(const vector<Collider*>& colliders)
{
	Collider* best_fit = nullptr;
	float best_time_to_collision = std::numeric_limits<float>::infinity();

	for (Collider* collider : colliders)
	{
		float time_to_collision = collider->getTimeToCollision(this);
		if (time_to_collision != NO_COLLISION && time_to_collision < best_time_to_collision)
		{
			best_fit = collider;
			best_time_to_collision = time_to_collision;
		}
	}

	return best_fit;
}
