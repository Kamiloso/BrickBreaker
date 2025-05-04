#include "MainMenu.h"
#include "SceneObject.h"
#include "Button.h"
#include "Text.h"
#include "Rectangle.h"
#include "Star.h"
#include "LevelGetter.h"
#include "Input.h"
#include "GameWindow.h"
#include "ParticleSystem.h"
#include "Sound.h"

#include <random>

MainMenu::MainMenu(int localScene)
{
	// Background
	mt19937 gen(Input::getGameWindowPtr()->getEntropy());
	uniform_int_distribution<> distRX(0, RX);
	uniform_int_distribution<> distRY(0, RY);
	uniform_int_distribution<> distNumOfStars(80, 105);

	for (int i = 0; i < distNumOfStars(gen); i++) {
		addObject(new Star(distRX(gen), distRY(gen), 2, &gen, 1));
	}
	
	background = dynamic_cast<Rectangle*>(
		addObject(new Rectangle(CX, CY, RX, RY, 0, sf::Color::Black, sf::Color::Black, 0))
		);

	title = dynamic_cast<Text*>(addObject(new Text(CX, CY - 230, L"PLATE BALL BRICK", 80, sf::Color(255, 255, 255))));
	subtitle = dynamic_cast<Text*>(addObject(new Text(CX, CY - 145, L"Alpha 0.1", 60, sf::Color(255, 255, 255))));
	
	// Main menu
	levels = dynamic_cast<Button*>(
		addObject(new Button(CX, CY - 10, 500, 95, COL::buttonBg, COL::buttonBold, L"LEVELS"))
		); levels->setEvent(1, false);

	instruction_btn = dynamic_cast<Button*>(
		addObject(new Button(CX, CY + 102, 500, 95, COL::buttonBg, COL::buttonBold, L"INSTRUCTION"))
		); 
	instruction_btn->setEvent(2, false);

	exit_btn = dynamic_cast<Button*>(
		addObject(new Button(CX, CY + 214, 500, 95, COL::buttonBg, COL::buttonBold, L"EXIT"))
		); exit_btn->setEvent(2, true);

	menu_object_list = { title, subtitle, levels, instruction_btn, exit_btn };

	// Level menu
	for (int i = 0; i < 40; i++) {
		int row = (i / 8) + 1;
		int col = (i % 8) + 1;
		float x_offset = -402.5 + 115 * (col - 1);
		float y_offset = -230 + 115 * (row - 1) - 55;

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
	
	/* -- EXIT BUTTON -- */
	Button* level_menu_exit_btn = dynamic_cast<Button*>(addObject(new Button(CX + 10000, CY + 290, 215, 90, COL::buttonExit, COL::buttonExitBold, L"EXIT")));
	level_menu_exit_btn->setEvent(3, false);
	menu_object_list.push_back(level_menu_exit_btn);

	// Instruction
	sf::Color instruction_bg_color = sf::Color(166, 200, 255);
	sf::Color instruction_title_color = sf::Color(105, 162, 255);
	sf::Color instruction_down_color = sf::Color(128, 176, 255);
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000, CY - 55, 800, 540, 10, instruction_bg_color, COL::buttonBold, 6)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000, 90, 800, 110, 10, instruction_title_color, COL::buttonBold, 7)));
	menu_object_list.push_back(addObject(new Text(CX + 20000, 90, L"INSTRUCTION", 55, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Text(CX + 20000, 185, L"1. Use the arrow keys to move the paddle.", 32, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Text(CX + 20000, 245, L"2. Change the ball's angle by adjusting", 32, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Text(CX + 20000, 285, L"the paddle's position.", 32, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Text(CX + 20000, 340, L"3. Clear each level by breaking all the bricks.", 32, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Text(CX + 20000, 400, L"4. How far can you get? Good luck!", 32, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000, 450, 800, 10, 0, COL::buttonBold, sf::Color::Black, 8)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000, 510, 10, 115, 0, COL::buttonBold, sf::Color::Black, 8)));
	menu_object_list.push_back(addObject(new Text(CX + 20000 - 200, 485, L"SOUNDS", 35, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Text(CX + 20000 + 200, 485, L"MUSIC", 35, COL::buttonBold, 10)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000, 510, 800, 128, 10, instruction_down_color, COL::buttonBold, 7)));
	
	// volume rects
	for (int i = 0; i < 10; i++)
	{
		float dx = (i - 4.5f) * 26.0f;
		Rectangle* rect_bg;

		rect_bg = new Rectangle(CX + 20000 - 200 + dx, 528, 30, 26, 4, sf::Color(150, 150, 150), COL::buttonBold, 7);
		sound_rects[i] = new Rectangle(CX + 20000 - 200 + dx, 528, 30, 26, 4, sf::Color::Green, COL::buttonBold, 8);
		menu_object_list.push_back(addObject(rect_bg));
		menu_object_list.push_back(addObject(sound_rects[i]));

		rect_bg = new Rectangle(CX + 20000 + 200 + dx, 528, 30, 26, 4, sf::Color(150, 150, 150), COL::buttonBold, 7);
		music_rects[i] = new Rectangle(CX + 20000 + 200 + dx, 528, 30, 26, 4, sf::Color::Green, COL::buttonBold, 8);
		menu_object_list.push_back(addObject(rect_bg));
		menu_object_list.push_back(addObject(music_rects[i]));
	}
	updateSoundBoxesVisibility();
	updateRealVolume();

	// volume regulation buttons
	constexpr float BT_OFFSET = 146.0f;
	constexpr float BT_SIZE = 35.0f;
	Button* bt1 = new Button(CX + 20000 - 200 - BT_OFFSET, 528, BT_SIZE, BT_SIZE, COL::buttonBg, COL::buttonBold, L""); // volume -
	Button* bt2 = new Button(CX + 20000 - 200 + BT_OFFSET, 528, BT_SIZE, BT_SIZE, COL::buttonBg, COL::buttonBold, L""); // volume +
	Button* bt3 = new Button(CX + 20000 + 200 - BT_OFFSET, 528, BT_SIZE, BT_SIZE, COL::buttonBg, COL::buttonBold, L""); // music -
	Button* bt4 = new Button(CX + 20000 + 200 + BT_OFFSET, 528, BT_SIZE, BT_SIZE, COL::buttonBg, COL::buttonBold, L""); // music +
	bt1->visualAdvanced(4); bt1->setEvent(5, false);
	bt2->visualAdvanced(4); bt2->setEvent(6, false);
	bt3->visualAdvanced(4); bt3->setEvent(7, false);
	bt4->visualAdvanced(4); bt4->setEvent(8, false);
	menu_object_list.push_back(addObject(bt1));
	menu_object_list.push_back(addObject(bt2));
	menu_object_list.push_back(addObject(bt3));
	menu_object_list.push_back(addObject(bt4));

	// volume regulation minus and plus
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000 - 200 - BT_OFFSET, 528, 16, 4, 0, COL::buttonBold, sf::Color::Black, 21)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000 - 200 + BT_OFFSET, 528, 16, 4, 0, COL::buttonBold, sf::Color::Black, 21)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000 - 200 + BT_OFFSET, 528, 4, 16, 0, COL::buttonBold, sf::Color::Black, 21)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000 + 200 - BT_OFFSET, 528, 16, 4, 0, COL::buttonBold, sf::Color::Black, 21)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000 + 200 + BT_OFFSET, 528, 16, 4, 0, COL::buttonBold, sf::Color::Black, 21)));
	menu_object_list.push_back(addObject(new Rectangle(CX + 20000 + 200 + BT_OFFSET, 528, 4, 16, 0, COL::buttonBold, sf::Color::Black, 21)));

	/* -- EXIT BUTTON -- */
	Button* instruction_exit_btn = dynamic_cast<Button*>(addObject(new Button(CX + 20000, CY + 290, 215, 90, COL::buttonExit, COL::buttonExitBold, L"EXIT")));
	instruction_exit_btn->setEvent(4, false);
	menu_object_list.push_back(instruction_exit_btn);

	// Changes local scene
	changeLocalScene(localScene);

	addObject(new ParticleSystem(CX, CY, 50, sf::Color::Magenta, 10, 0.5, "1", 100));
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

		if (event_number >= 5 && event_number <= 8) // volume / music settings changed
		{
			char sound = LevelGetter::getProgress().sound_volume;
			char music = LevelGetter::getProgress().music_volume;

			if (event_number == 5 && sound > 0) sound--;
			if (event_number == 6 && sound < 10) sound++;
			if (event_number == 7 && music > 0) music--;
			if (event_number == 8 && music < 10) music++;

			LevelGetter::changeSoundVolume(sound);
			LevelGetter::changeMusicVolume(music);

			updateSoundBoxesVisibility();
			updateRealVolume();
		}
	}

	// Exit with escape
	if (current_local_screen != 0)
	{
		if (Input::isKeyboardPressed(sf::Keyboard::Escape, Input::Down))
			changeLocalScene(-current_local_screen);
	}
}

void MainMenu::changeLocalScene(int i) {
	current_local_screen += i;
	for (SceneObject* object : menu_object_list) {
		if (object == nullptr) continue;
		auto object_pos = object->getPosition();
		object->setPosition(object_pos[0] - i * 10000, object_pos[1]);
	}
}

void MainMenu::updateSoundBoxesVisibility()
{
	char sound = LevelGetter::getProgress().sound_volume;
	char music = LevelGetter::getProgress().music_volume;

	for (int i = 0; i < 10; i++)
	{
		sound_rects[i]->setVisible(i < sound);
		music_rects[i]->setVisible(i < music);
	}
}

void MainMenu::updateRealVolume(bool playtest)
{
	char sound = LevelGetter::getProgress().sound_volume;
	char music = LevelGetter::getProgress().music_volume;

	static float sound_remember = -1.0f;
	static float music_remember = -1.0f;

	float target_sound = sound * 0.1f;
	float target_music = music * 0.1f;

	Sound::setSoundVolume(target_sound);
	Sound::setMusicVolume(target_music);

	if (sound_remember != target_sound)
	{
		if (sound_remember != -1.0f && playtest)
			Sound::playSound("1");
		sound_remember = target_sound;
	}

	if (music_remember != target_music)
	{
		//if (music_remember != -1.0f && playtest)
			//Sound::playMusic("1");
		music_remember = target_music;
	}
}
