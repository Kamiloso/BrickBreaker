#include "SceneObject.h"
#include "GameWindow.h"

sf::Vector2<float> SceneObject::getPosition()
{
	return sf::Vector2<float>(x, y);
}

void SceneObject::setPosition(sf::Vector2<float> _position)
{
	x = _position.x;
	y = _position.y;
}

float SceneObject::getRotation()
{
	return rot;
}

void SceneObject::setRotation(float _rot)
{
	rot = _rot;
}

void TempCircle::draw(GameWindow* game_window)
{
	game_window->drawCircle(x, y, r, sf::Color::Black);
	game_window->drawCircle(x, y, r - 20, color);
}

void TempCircle::update(float delta_time)
{
	x += 100 * delta_time;
}

int TempCircle::getEvent()
{
	if (x >= RX)
		return 1;
	else
		return 0;
}

int TempCircle::getEventToScene()
{
	if (x >= RX - 200)
		return 1;
	else
		return 0;
}
