#pragma once
#include "Circle.h"
#include <vector>

class Ball : public Circle
{
public:
	Ball(float _x, float _y, float _vx, float _vy, int _layer = 12);
	void step(float delta_time);
	void setVelocity(float _vx, float _vy);
	void setVelocityByAngle(float angle, float magnitude); // degrees
	vector<float> getVelocity() const;
	float getVelocityAngle() const;
	float getVelocityMagnitude() const;

protected:
	float vx;
	float vy;
};

