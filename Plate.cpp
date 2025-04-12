#include "Plate.h"
#include "GameWindow.h"

Plate::Plate(float _x, float _y, float _left_border, float _right_border, int _layer)
	: Rectangle(_x, _y, 120, 20, 2, sf::Color::Yellow, sf::Color::Black, _layer),
	left_border(_left_border), right_border(_right_border) {}

void Plate::earlyUpdate(float delta_time)
{
	// plate movement
	if (!input_data->game_window->isPause())
	{
		const float tl_border = left_border + wx / 2;
		const float tr_border = right_border - wx / 2;

		if (input_data->mouse_x >= tl_border && input_data->mouse_x <= tr_border)
		{
			x = input_data->mouse_x;
		}
		else // outside border correction
		{
			if (input_data->mouse_x < tl_border)
				x = tl_border;
			else
				x = tr_border;
		}
	}
}
