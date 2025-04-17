#include "Plate.h"
#include "GameWindow.h"
#include "Input.h"

#include <cmath>

template<typename T>
static int signum(T x) {
	return (T(0) < x) - (x < T(0));
}

Plate::Plate(float _x, float _y, float _left_border, float _right_border, int _layer)
	: Rectangle(_x, _y, 120, 20, 2, sf::Color::Yellow, sf::Color::Black, _layer),
	left_border(_left_border), right_border(_right_border) {}

void Plate::earlyUpdate(float delta_time)
{
	// plate movement
	if (!Input::getGameWindowPtr()->isPause())
	{
		const float tl_border = left_border + wx / 2;
		const float tr_border = right_border - wx / 2;

		if (false) // Old control
		{
			float mouse_x = Input::getMousePosition()[0];
			if (mouse_x >= tl_border && mouse_x <= tr_border)
			{
				x = mouse_x;
			}
			else // outside border correction
			{
				if (mouse_x < tl_border)
					x = tl_border;
				else
					x = tr_border;
			}
		}

		// Plate constants
		constexpr float PLATE_ACCELERATION = 1.0f;		// Acceleration size
		constexpr float PLATE_DRAG = -0.12f;			// Drag size
		constexpr float PLATE_MAX_SPEED = 16.0f;		// Default max speed
		constexpr float PLATE_BRAKE_FACTOR = 1.5f;		// Deacceleration is multiplied by this
		constexpr float PLATE_ADDITIVE_DRAG = 1.5f;		// Minimum drag speed coofficient

		// Input read
		bool special_action = Input::isKeyboardPressed(sf::Keyboard::Up, Input::Down) || Input::isKeyboardPressed(sf::Keyboard::Space, Input::Down);
		bool want_right = Input::isKeyboardPressed(sf::Keyboard::Right) || Input::isKeyboardPressed(sf::Keyboard::D);
		bool want_left = Input::isKeyboardPressed(sf::Keyboard::Left) || Input::isKeyboardPressed(sf::Keyboard::A);
		int input_want = want_right - want_left;

		// Acceleration
		float acceleration = PLATE_ACCELERATION * input_want;
		if (signum(acceleration) != signum(speed))
			acceleration *= PLATE_BRAKE_FACTOR;
		speed += acceleration;

		// Drag
		if (signum(acceleration) != signum(speed))
		{
			float drag_acceleration = PLATE_DRAG * (speed + 1.5f * signum(speed));
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
		x += speed;
		if (x < tl_border)
		{
			x = tl_border;
			speed = 0.0f;
		}
		if (x > tr_border)
		{
			x = tr_border;
			speed = 0.0f;
		}
	}
}
