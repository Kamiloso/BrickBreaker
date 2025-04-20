#pragma once
#include "Rectangle.h"

using namespace std;

class Plate : public Rectangle
{
public:
	Plate(float _x, float _y, float _left_border, float _right_border, int _layer = 14);
	void earlyUpdate(float delta_time) override;

private:
	const float left_border;
	const float right_border;
	float speed = 0.0f; // speed on the X axis [pixels / second]
};
