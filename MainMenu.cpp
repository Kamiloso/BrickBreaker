#include "MainMenu.h"
#include "SceneObject.h"
#include "Button.h"
#include "Text.h"
#include "Rectangle.h"
#include "Star.h"
#include <random>

MainMenu::MainMenu()
{
	// Tlo
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distRX(0, RX);
	uniform_int_distribution<> distRY(0, RY);
	uniform_int_distribution<> distNumOfStars(80, 105);

	for (int i = 0; i < distNumOfStars(gen); i++) {
		addObject(new Star(distRX(gen), distRY(gen), 1, &gen, 1));
	}
	
	background = dynamic_cast<Rectangle*>(
		addObject(new Rectangle(RX / 2, RY / 2, RX, RY, 0, sf::Color::Black, sf::Color::Black, 0))
		);

		addObject(new Text(RX / 2, RY / 2 - 200, L"BRICK BALL PLATE", 80, sf::Color(255, 255, 255)));
		addObject(new Text(RX / 2, RY / 2 - 115, L"Alpha 0.1", 80, sf::Color(255, 255, 255)));
	
	// Przyciski menu
	levels = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 - 210, RY / 2 + 40, 400, 100, sf::Color::Cyan, sf::Color(41, 33, 33), L"LEVELS"))
		); levels->setEvent(1001, true);

	endless_btn = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 + 210, RY / 2 + 40, 400, 100, sf::Color::Cyan, sf::Color(41, 33, 33), L"ENDLESS"))
		); endless_btn->setEvent(1002, true);

	instruction_btn = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 - 210, RY / 2 + 160, 400, 100, sf::Color::Cyan, sf::Color(41, 33, 33), L"INSTRUCTION"))
		); 
	//instruction_btn->setEvent(2, true);

	exit_btn = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 + 210, RY / 2 + 160, 400, 100, sf::Color::Cyan, sf::Color(41, 33, 33), L"EXIT"))
		); exit_btn->setEvent(2, true);
}

void MainMenu::sceneUpdate(float delta_time)
{
	for (SceneObject* object : object_list)
	{
		// Button scene event reactions
		Button* button = dynamic_cast<Button*>(object);
		if (button != nullptr)
		{
			vector<float> button_pos = button->getPosition();
			if (button->getEventToScene() == 1)
			{
				button->setPosition(button_pos[0] + 100, button_pos[1]);
			}
		}
	}
}
