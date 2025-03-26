#include "MainMenu.h"
#include "SceneObject.h"

MainMenu::MainMenu()
{
	addObject(new TempCircle(200, 200, 60, sf::Color::Magenta));
	addObject(new TempCircle(RX / 2, RY / 2, 100, sf::Color::Red));
	addObject(new TempCircle(RX - 200, RY - 200, 140, sf::Color::Cyan));
}
