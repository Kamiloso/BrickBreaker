#pragma once
#include "Rectangle.h"

using namespace std;

class Plate : public Rectangle
{
public:
	Plate(float _x, float _y, float _left_border, float _right_border, int _layer = 8);
	void earlyUpdate(float delta_time) override;
	void draw(GameWindow* game_window) override;

	void setDefaultWidth(float width); // overwrites default_width
	void changeWidth(int delta_width_modifier); // changes width from power-up
	void reverseControl(); // reverses control or returns to a normal state
	bool isReversed() const { return reversed; } // reversed getter

private:
	const float left_border;
	const float right_border;
	float default_width;
	int width_modifier = 0;
	float speed = 0.0f; // speed on the X axis [pixels / second]
	bool reversed = false; // has reversed control?

	void positionCorrection(bool reset_velocity); // corrects position in such way to prevent overlapping walls
};
