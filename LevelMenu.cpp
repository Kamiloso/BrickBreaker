#include "LevelMenu.h"
#include "SceneObject.h"

LevelMenu::LevelMenu()
{
	addObject(new TempCircle(200, 200, 60, sf::Color::Red));
	addObject(new TempCircle(RX / 2, RY / 2, 100, sf::Color::Magenta));
	addObject(new TempCircle(RX - 200, RY - 200, 140, sf::Color::Yellow));
}

void LevelMenu::sceneUpdate(float delta_time)
{

}
