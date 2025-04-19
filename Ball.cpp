#include "Ball.h"
#include "GameWindow.h"
#include "GameScene.h"
#include "Sound.h"

#include <vector>
#include <cmath>

Ball::Ball(float _x, float _y, float _vx, float _vy, int _layer)
	: Circle(_x, _y, 15, 3, sf::Color::Green, sf::Color::Black, _layer),
	vx(_vx), vy(_vy) {}

void Ball::step(float delta_time)
{
	x += vx * delta_time;
	y += vy * delta_time;
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
