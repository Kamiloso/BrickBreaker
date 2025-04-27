#include "Plate.h"
#include "GameWindow.h"
#include "Input.h"

#include <cmath>

template<typename T>
static int signum(T x) {
	return (T(0) < x) - (x < T(0));
}

Plate::Plate(float _x, float _y, float _left_border, float _right_border, int _layer)
	: Rectangle(_x, _y, 120, 20, 3, COL::plate, sf::Color::Black, _layer),
	left_border(_left_border), right_border(_right_border), default_width(120) {}

void Plate::earlyUpdate(float delta_time)
{
	// plate movement
	if (!Input::getGameWindowPtr()->isPause())
	{
		// Plate constants
		constexpr float PLATE_ACCELERATION = 4000.0f;	// Acceleration size
		constexpr float PLATE_DRAG = -500.0f;			// Drag size
		constexpr float PLATE_MAX_SPEED = 1200.0f;		// Default max speed
		constexpr float PLATE_BRAKE_FACTOR = 2.0f;		// Deacceleration is multiplied by this
		constexpr float PLATE_ADDITIVE_DRAG = 1.5f;		// Minimum drag speed coofficient

		// Input read
		bool special_action = Input::isKeyboardPressed(sf::Keyboard::Up, Input::Down) || Input::isKeyboardPressed(sf::Keyboard::Space, Input::Down);
		bool want_right = Input::isKeyboardPressed(sf::Keyboard::Right) || Input::isKeyboardPressed(sf::Keyboard::D);
		bool want_left = Input::isKeyboardPressed(sf::Keyboard::Left) || Input::isKeyboardPressed(sf::Keyboard::A);
		int input_want = (want_right - want_left) * (reversed ? -1 : 1);

		// Acceleration
		float acceleration = PLATE_ACCELERATION * input_want * delta_time;
		if (signum(acceleration) != signum(speed) && speed != 0.0f)
			acceleration = acceleration * PLATE_BRAKE_FACTOR;
		speed += acceleration;

		// Drag
		if (signum(acceleration) != signum(speed))
		{
			float drag_acceleration = PLATE_DRAG * (speed / 60.0f + 1.5f * signum(speed)) * delta_time;
			if (signum(speed + drag_acceleration) == signum(speed))
				speed += drag_acceleration;
			else
				speed = 0.0f;
		}

		// Max speed apply
		if (speed >= PLATE_MAX_SPEED)
			speed = PLATE_MAX_SPEED;
		if (speed <= -PLATE_MAX_SPEED)
			speed = -PLATE_MAX_SPEED;

		// Moving plate based on speed
		x += speed * delta_time;
		
		// Prevent overlapping walls
		positionCorrection(true);
	}
}

void Plate::draw(GameWindow* game_window)
{
	game_window->drawRectangle(x, y, wx, wy, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2, wy - bold * 2, color);

	if (reversed) { // reverse strips
		//game_window->drawRectangle(x, y, wx - (wy - bold), bold, color_bold);
		//game_window->drawRectangle(x, y, (wy - 3 * bold) / 2, bold, color);
	}
}

void Plate::setDefaultWidth(float width)
{
	default_width = width;
	wx = width;
}

void Plate::changeWidth(int delta_width_modifier)
{
	float PLATE_SIZES[3] = { 0.70f, 1.00f, 1.40f };

	width_modifier += delta_width_modifier;

	if (width_modifier < -1)
		width_modifier = -1;

	if (width_modifier > 1)
		width_modifier = 1;

	wx = default_width * PLATE_SIZES[1 + width_modifier];
	positionCorrection(false);
}

void Plate::reverseControl()
{
	if (reversed) {
		reversed = false;
		color = COL::plate;
	}
	else {
		reversed = true;
		color = COL::reversedPlate;
	}
}

void Plate::positionCorrection(bool reset_velocity)
{
	const float tl_border = left_border + wx / 2;
	const float tr_border = right_border - wx / 2;
	if (x < tl_border)
	{
		x = tl_border;
		if(reset_velocity)
			speed = 0.0f;
	}
	if (x > tr_border)
	{
		x = tr_border;
		if (reset_velocity)
			speed = 0.0f;
	}
}
