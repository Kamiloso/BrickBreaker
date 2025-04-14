#include "MainMenu.h"
#include "SceneObject.h"
#include "Button.h"
#include "Text.h"
#include "Rectangle.h"
#include "Star.h"
#include <random>
#include "LevelGetter.h"

//#include <iostream>

MainMenu::MainMenu(int localScene)
{
	// Tlo
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distRX(0, RX);
	uniform_int_distribution<> distRY(0, RY);
	uniform_int_distribution<> distNumOfStars(80, 105);

	for (int i = 0; i < distNumOfStars(gen); i++) {
		addObject(new Star(distRX(gen), distRY(gen), 2, &gen, 1));
	}
	
	background = dynamic_cast<Rectangle*>(
		addObject(new Rectangle(RX / 2, RY / 2, RX, RY, 0, sf::Color::Black, sf::Color::Black, 0))
		);

	title = dynamic_cast<Text*>(addObject(new Text(RX / 2, RY / 2 - 200, L"BRICK BALL PLATE", 80, sf::Color(255, 255, 255))));
	subtitle = dynamic_cast<Text*>(addObject(new Text(RX / 2, RY / 2 - 115, L"Alpha 0.1", 60, sf::Color(255, 255, 255))));
	
	// Main menu
	levels = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 - 210, RY / 2 + 40, 400, 100, sf::Color::Cyan, sf::Color(30, 36, 107), L"LEVELS"))
		); levels->setEvent(1, false);

	endless_btn = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 + 210, RY / 2 + 40, 400, 100, sf::Color::Cyan, sf::Color(30, 36, 107), L"ENDLESS"))
		); endless_btn->setEvent(1002, true);

	instruction_btn = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 - 210, RY / 2 + 160, 400, 100, sf::Color::Cyan, sf::Color(30, 36, 107), L"INSTRUCTION"))
		); 
	instruction_btn->setEvent(2, false);

	exit_btn = dynamic_cast<Button*>(
		addObject(new Button(RX / 2 + 210, RY / 2 + 160, 400, 100, sf::Color::Cyan, sf::Color(30, 36, 107), L"EXIT"))
		); exit_btn->setEvent(2, true);

	menu_object_list = { title, subtitle, levels, endless_btn, instruction_btn, exit_btn };

	// Level menu

	// Do usuniecia
	for (int i = 0; i < 11; i++) {
		LevelGetter::setLevelFlag(i, 1);
	}
	// *

	for (int i = 0; i < 40; i++) {
		int row = (i / 8) + 1;
		int col = (i % 8) + 1;
		float x_offset = -402.5 + 115 * (col - 1);
		float y_offset = -230 + 115 * (row - 1);

		bool locked = true;
		if (i == 0 || LevelGetter::isFlagSet(i - 1, 1)) {
			locked = false;
		}

		Button* level_btn = new Button(CX + 10000 + x_offset, CY + y_offset, 100, 100, (LevelGetter::isFlagSet(i, 1)) ? sf::Color(111, 170, 201) : sf::Color(3, 252, 102), sf::Color(30, 36, 107), to_wstring(i + 1));
		addObject(level_btn);
		menu_object_list.push_back(level_btn);

		if (locked == true) continue;
		level_btn->setEvent(3000 + i, true);
	}

	// Instruction
	Button* instruction_exit_btn = dynamic_cast<Button*>(addObject(new Button(CX + 20000, CY, 150, 100, sf::Color(232, 26, 187), sf::Color(30, 36, 107), L"EXIT")));
	instruction_exit_btn->setEvent(3, false);
	menu_object_list.push_back(instruction_exit_btn);
}

void MainMenu::sceneUpdate(float delta_time)
{
	for (SceneObject* object : object_list)
	{
		Button* button = dynamic_cast<Button*>(object);
		if (button == nullptr) continue;
		int event_number = button->getEventToScene();

		// levels_btn
		if (event_number == 1) changeView(1);
		// instruction_btn
		if (event_number == 2) changeView(2);
		// instruction_exit_btn
		if (event_number == 3) changeView(-2);
	}
}

void MainMenu::changeView(int i) {
	for (SceneObject* object : menu_object_list) {
		if (object == nullptr) continue;
		auto object_pos = object->getPosition();
		object->setPosition(object_pos[0] - i * 10000, object_pos[1]);
	}
}