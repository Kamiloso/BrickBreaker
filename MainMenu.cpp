#include "MainMenu.h"
#include "SceneObject.h"
#include "Rectangle.h"

MainMenu::MainMenu()
{
	for(int x = 45; x <= RX; x += 90)
		addObject(new Rectangle(x, 200, 90, 90, 10, sf::Color::White));

	addObject(new TempCircle(RX / 2, RY / 2, 100, sf::Color::Red));
}

void MainMenu::sceneUpdate(float delta_time)
{

}
