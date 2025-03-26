#include "SceneObject.h"
#include "GameWindow.h"

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
