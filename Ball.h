#pragma once
#include "Circle.h"

class Ball : public Circle
{
public:
	Ball(float _x, float _y, float _vx, float _vy, int _layer = 12);
	void step(float delta_time);
	void setVelocityByAngle(float angle, float magnitude);

protected:
	float vx;
	float vy;
};

