#include "MainMenu.h"
#include "SceneObject.h"
#include "Button.h"

MainMenu::MainMenu()
{
	for(int x = 45; x <= RX; x += 90)
		addObject(new Rectangle(x, 200, 90, 90, 10, sf::Color::White));

	addObject(new TempCircle(RX / 2, RY / 2, 150, sf::Color::Red));

	addObject(new Button(RX / 2, RY / 2, 400, 100, sf::Color::Cyan, L"PLAY"));
}

void MainMenu::sceneUpdate(float delta_time)
{
	for (SceneObject* object : object_list)
	{
		TempCircle* temp_circle = dynamic_cast<TempCircle*>(object);
		if (temp_circle != nullptr)
			temp_circle->step(delta_time);
	}
}
