#include "Ball.h"
#include "GameWindow.h"

Ball::Ball(float pos_x, float pos_y, float _r, int _layer)
	: SceneObject(pos_x, pos_y,_layer), r(_r), color(sf::Color::Green) {}

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
		return 3;
	else
		return 0;
}
