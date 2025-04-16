#include "Plate.h"
#include "GameWindow.h"
#include "Input.h"

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

		// Input read
		int input_want = 0;
		bool special_action = Input::isKeyboardPressed(sf::Keyboard::Up, Input::Down) || Input::isKeyboardPressed(sf::Keyboard::Space, Input::Down);
		input_want += Input::isKeyboardPressed(sf::Keyboard::Right) || Input::isKeyboardPressed(sf::Keyboard::D);
		input_want -= Input::isKeyboardPressed(sf::Keyboard::Left) || Input::isKeyboardPressed(sf::Keyboard::A);

		// Acceleration
		speed = input_want * 10;

		// Moving plate based on velocity
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
