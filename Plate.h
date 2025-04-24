#pragma once
#include "Rectangle.h"

using namespace std;

class Plate : public Rectangle
{
public:
	Plate(float _x, float _y, float _left_border, float _right_border, int _layer = 8);
	void earlyUpdate(float delta_time) override;
	void setDefaultWidth(float width);

private:
	const float left_border;
	const float right_border;
	float default_width;
	float speed = 0.0f; // speed on the X axis [pixels / second]
};
