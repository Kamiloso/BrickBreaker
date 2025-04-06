#include "MainMenu.h"
#include "SceneObject.h"
#include "Button.h"
#include "Text.h"

MainMenu::MainMenu()
{
	title = dynamic_cast<Text*>(
		addObject(new Text(RX / 2, RY / 2 - 250, L"Brick, Ball, Plate - Alpha 0.1", 80))
		);

	button1 = dynamic_cast<Button*>(
		addObject(new Button(RX / 2, RY / 2 - 70, 400, 100, sf::Color::Cyan, L"MOVE BUTTON"))
		); button1->setEvent(1, false);

	button2 = dynamic_cast<Button*>(
		addObject(new Button(RX / 2, RY / 2 + 50, 400, 100, sf::Color::Cyan, L"CHANGE SCENE"))
		); button2->setEvent(1001, true);

	button3 = dynamic_cast<Button*>(
		addObject(new Button(RX / 2, RY / 2 + 170, 400, 100, sf::Color::Cyan, L"EXIT"))
		); button3->setEvent(2, true);

	button4 = dynamic_cast<Button*>(
		addObject(new Button(200,50, 400, 100, sf::Color::Cyan, L"PLAY"))
		); button4->setEvent(1002, true);
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
