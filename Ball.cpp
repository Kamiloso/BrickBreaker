#include "Ball.h"
#include "GameWindow.h"

Ball::Ball(float pos_x, float pos_y, float _r, sf::Color _color,int _layer)
	: SceneObject(pos_x, pos_y,_layer), r(_r), color(_color) {}

void Ball::draw(GameWindow* game_window)
{
	game_window->drawCircle(x,y, r, color);
}
void Ball::step(float delta_time) 
{
	x += vx*delta_time;
	y += vy*delta_time;
}


int Ball::getEventToScene()
{
	if (y >= RY + r)
		return 1;
	else
		return 0;
}
