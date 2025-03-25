#include "SceneObject.h"
#include "GameWindow.h"

void TempCircle::draw(GameWindow* game_window)
{
	game_window->drawCircle(x, y, r, sf::Color::Black);
	game_window->drawCircle(x, y, r - 20, color);
}
