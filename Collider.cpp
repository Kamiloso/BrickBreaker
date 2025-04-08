#include "Collider.h"
#include "GameWindow.h"

Collider::Collider(float _x, float _y, float _wx, float _wy,float _left_border,float _right_border, sf::Color _color, int _layer)
	: SceneObject(_x,_y,_layer), wx(_wx),wy(_wy),color(_color)
{
	left_border = _left_border-wx;
	right_border = RX + _right_border+wx;
}
void Collider::draw(GameWindow* game_window)
{
	game_window->drawRectangle(x,y,wx,wy,color);
}

void Collider::earlyUpdate(float delta_time)
{
	if (input_data->mouse_x > left_border && input_data->mouse_x < right_border)
	{
		x = input_data->mouse_x;
	}
	else if (input_data->mouse_x <= left_border)
	{
		x = left_border;
	}
	else if (input_data->mouse_x >= right_border)
	{
		x = right_border;
	}
}
