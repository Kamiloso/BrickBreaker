#include "GameScene.h"
#include "SceneObject.h"
#include "Button.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "Text.h"

GameScene::GameScene(int _level) : level(_level)
{
	// --- Create game objects ---
	wstring level_text = (level + 1) < 10 ? L"LEVEL 0" : L"LEVEL ";
	level_text += to_wstring(level + 1) + L" / " + to_wstring(LEVELS);
	level_num_text = dynamic_cast<Text*>(addObject(new Text(RX - 240, 50, level_text, 70)));

	left_wall = dynamic_cast<Rectangle*>(addObject(new Rectangle(0, 0,left_margin, RY * 2,0, sf::Color::White, sf::Color::Black, 1)));
	right_wall = dynamic_cast<Rectangle*>(addObject(new Rectangle(RX, 0,right_margin, RY * 2,0, sf::Color::White, sf::Color::Black, 1)));
	ball1 = dynamic_cast<Ball*>(addObject(new Ball(RX/2,300,20,1)));
	collider1 = dynamic_cast<Collider*>(addObject(new Collider(RX/2, RY - 20, 100, 10, left_margin, right_margin, sf::Color::Green, 2)));
	grid1 = dynamic_cast<Grid*>(addObject(new Grid(RX/2,0,RX-left_margin,(RX-left_margin)/4, ROWS,COLS, 1)));
	populateGrid(grid1);

	// --- Create game UI ---
	sf::Color pause_color(60, 60, 60, 200);
	sf::Color win_color(0, 100, 0, 200);
	sf::Color defeat_color(100, 0, 0, 200);
	sf::Color empty_color(0, 0, 0, 0);

	const float CPX1 = CX + 10000.0f; // pause middle X
	const float CPY1 = CY; // pause middle Y
	const float CPX2 = CX + 20000.0f; // win middle X
	const float CPY2 = CY; // win middle Y
	const float CPX3 = CX + 30000.0f; // defeat middle X
	const float CPY3 = CY; // defeat middle Y

	// Button declarations
	Button* button_menu_pause = dynamic_cast<Button*>(
		addObject(new Button(CPX1, CPY1 + 220, 450, 90, sf::Color::White, sf::Color::Black, L"BACK TO MENU"))
		); button_menu_pause->setEvent(2001, true);

	Button* button_retry_pause = dynamic_cast<Button*>(
		addObject(new Button(CPX1, CPY1 + 115, 450, 90, sf::Color::White, sf::Color::Black, L"RESET"))
		); button_retry_pause->setEvent(3000 + level, true);

	Button* button_resume_pause = dynamic_cast<Button*>(
		addObject(new Button(CPX1, CPY1 + 10, 450, 90, sf::Color::White, sf::Color::Black, L"RESUME"))
		); button_resume_pause->setEvent(2, false);

	Button* button_menu_win = dynamic_cast<Button*>(
		addObject(new Button(CPX2 - 210, CPY2 + 150, 400, 100, sf::Color::Green, sf::Color::Black, L"BACK TO MENU"))
		); button_menu_win->setEvent(2001, true);

	Button* button_next_win = dynamic_cast<Button*>(
		addObject(new Button(CPX2 + 210, CPY2 + 150, 400, 100, sf::Color::Green, sf::Color::Black, L"NEXT LEVEL"))
		); if (level + 1 < LEVELS) button_next_win->setEvent(3000 + level + 1, true);

	Button* button_menu_defeat = dynamic_cast<Button*>(
		addObject(new Button(CPX3 - 210, CPY3 + 150, 400, 100, sf::Color::Red, sf::Color::Black, L"BACK TO MENU"))
		); button_menu_defeat->setEvent(2001, true);

	Button* button_retry_defeat = dynamic_cast<Button*>(
		addObject(new Button(CPX3 + 210, CPY3 + 150, 400, 100, sf::Color::Red, sf::Color::Black, L"RETRY"))
		); button_retry_defeat->setEvent(3000 + level, true);

	// Movable array declaration
	pause_menu_objects = {

		// PAUSE
		addObject(new Rectangle(CPX1, CPY1, 3000, 3000, 0.0f, pause_color, empty_color, 18)), // pause background
		addObject(new Text(CPX1, CPY1 - 175, L"PAUSE", 220, sf::Color::Black)), // win text
		button_menu_pause,
		button_retry_pause,
		button_resume_pause,

		// WIN
		addObject(new Rectangle(CPX2, CPY2, 3000, 3000, 0.0f, win_color, empty_color, 18)), // win background
		addObject(new Text(CPX2, CPY2 - 80, L"YOU WIN", 220, sf::Color::Black)), // win text
		button_menu_win,
		button_next_win,

		// DEFEAT
		addObject(new Rectangle(CPX3, CPY3, 3000, 3000, 0.0f, defeat_color, empty_color, 18)), // defeat background
		addObject(new Text(CPX3, CPY3 - 80, L"DEFEAT", 220, sf::Color::Black)), // defeat text
		button_menu_defeat,
		button_retry_defeat
	};
}

GameScene::~GameScene()
{
	// Disable pause after leaving game scene
	input_data->game_window->setPause(false);
}

void GameScene::sceneUpdate(float delta_time)
{
	// Scene event handling
	bool end_now = false;
	bool pause_now = false;
	bool win_now = false;
	for (SceneObject* obj : object_list)
	{
		int event = obj->getEventToScene();
		if (event == 0)
			continue;

		if (event == 1) // defeat
			end_now = true;

		if (event == 2) // pause toggle
			pause_now = true;

		if (event == 3) { // win
			end_now = true;
			win_now = true;
		}
	}

	// Escape pause toggle
	if (input_data->escape && !was_escape_pressed)
		pause_now = true;
	
	// Local screen decide
	if (end_now)
	{
		if (win_now)
			local_screen = 2; // win
		else
			local_screen = 3; // defeat
	}	
	else
	{
		if (pause_now)
		{
			if (local_screen == 0) local_screen = 1; // pause
			else if (local_screen == 1) local_screen = 0; // none
		}
	}

	// Local screen togglator
	if (local_screen_before != local_screen)
	{
		input_data->game_window->setPause(local_screen != 0);

		float delta_move = -10000.0f * (local_screen - local_screen_before);
		for (SceneObject* obj : pause_menu_objects)
		{
			auto pos0 = obj->getPosition();
			obj->setPosition(pos0[0] + delta_move, pos0[1]);
		}
	}

	// Ball movement
	if (ball1 != nullptr) 
	{
		ball1->step(delta_time);
	}

	// Past set
	was_escape_pressed = input_data->escape;
	local_screen_before = local_screen;
}

void GameScene::populateGrid(Grid* grid)
{
	for (size_t row = 0; row < ROWS; row++)
	{
		for (size_t col = 0; col < COLS; col++)
		{
			addObject(new Brick(
				left_margin/2 + grid->position_x[col]-grid->brickw/2,
				grid->position_y[row]-grid->brickh/2)
			);
		}
	}
}
