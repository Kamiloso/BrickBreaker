#include "MainMenu.h"
#include "SceneObject.h"
#include "Button.h"
#include "Text.h"
#include "Rectangle.h"
#include "Star.h"
#include <random>
#include "LevelGetter.h"

MainMenu::MainMenu(int localScene)
{
	// Background
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distRX(0, RX);
	uniform_int_distribution<> distRY(0, RY);
	uniform_int_distribution<> distNumOfStars(80, 105);

	for (int i = 0; i < distNumOfStars(gen); i++) {
		addObject(new Star(distRX(gen), distRY(gen), 2, &gen, 1));
	}
	
	background = dynamic_cast<Rectangle*>(
		addObject(new Rectangle(CX, CY, RX, RY, 0, sf::Color::Black, sf::Color::Black, 0))
		);

	title = dynamic_cast<Text*>(addObject(new Text(CX, CY - 200, L"PLATE BALL BRICK", 80, sf::Color(255, 255, 255))));
	subtitle = dynamic_cast<Text*>(addObject(new Text(CX, CY - 115, L"Alpha 0.1", 60, sf::Color(255, 255, 255))));
	
	// Main menu
	levels = dynamic_cast<Button*>(
		addObject(new Button(CX - 210, CY + 40, 400, 100, COL::buttonBg, COL::buttonBold, L"LEVELS"))
		); levels->setEvent(1, false);

	endless_btn = dynamic_cast<Button*>(
		addObject(new Button(CX + 210, CY + 40, 400, 100, COL::buttonBg, COL::buttonBold, L"ENDLESS"))
		); endless_btn->setEvent(1002, true);

	instruction_btn = dynamic_cast<Button*>(
		addObject(new Button(CX - 210, CY + 160, 400, 100, COL::buttonBg, COL::buttonBold, L"INSTRUCTION"))
		); 
	instruction_btn->setEvent(2, false);

	exit_btn = dynamic_cast<Button*>(
		addObject(new Button(CX + 210, CY + 160, 400, 100, COL::buttonBg, COL::buttonBold, L"EXIT"))
		); exit_btn->setEvent(2, true);

	menu_object_list = { title, subtitle, levels, endless_btn, instruction_btn, exit_btn };

	// Level menu

	// To be deleted
	for (int i = 0; i < 11; i++) {
		LevelGetter::setLevelFlag(i, 1);
	}
	// *

	for (int i = 0; i < 40; i++) {
		int row = (i / 8) + 1;
		int col = (i % 8) + 1;
		float x_offset = -402.5 + 115 * (col - 1);
		float y_offset = -230 + 115 * (row - 1) - 60;

		bool locked = true;
		if (i == 0 || LevelGetter::isFlagSet(i - 1, 1)) {
			locked = false;
		}

		Button* level_btn = new Button(CX + 10000 + x_offset, CY + y_offset, 100, 100, (LevelGetter::isFlagSet(i, 1)) ? COL::levelComplete : COL::levelUnlocked, COL::buttonBold, to_wstring(i + 1));
		addObject(level_btn);
		menu_object_list.push_back(level_btn);

		if (locked == true) continue;
		level_btn->setEvent(3000 + i, true);
	}
	Button* level_menu_exit_btn = dynamic_cast<Button*>(addObject(new Button(CX + 10000, CY + 290, 215, 90, COL::buttonBg, COL::buttonBold, L"EXIT")));
	level_menu_exit_btn->setEvent(3, false);
	menu_object_list.push_back(level_menu_exit_btn);

	// Instruction
	Button* instruction_exit_btn = dynamic_cast<Button*>(addObject(new Button(CX + 20000, CY + 290, 215, 90, COL::buttonBg, COL::buttonBold, L"EXIT")));
	instruction_exit_btn->setEvent(4, false);
	menu_object_list.push_back(instruction_exit_btn);

	// Changes local scene
	changeLocalScene(localScene);
}

void MainMenu::sceneUpdate(float delta_time)
{
	for (SceneObject* object : object_list)
	{
		Button* button = dynamic_cast<Button*>(object);
		if (button == nullptr) continue;
		int event_number = button->getEventToScene();

		// levels_btn
		if (event_number == 1) changeLocalScene(1);
		// instruction_btn
		if (event_number == 2) changeLocalScene(2);
		// level_menu_exit_btn
		if (event_number == 3) changeLocalScene(-1);
		// instruction_exit_btn
		if (event_number == 4) changeLocalScene(-2);
	}
}

void MainMenu::changeLocalScene(int i) {
	for (SceneObject* object : menu_object_list) {
		if (object == nullptr) continue;
		auto object_pos = object->getPosition();
		object->setPosition(object_pos[0] - i * 10000, object_pos[1]);
	}
}