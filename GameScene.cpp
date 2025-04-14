#include "GameScene.h"
#include "SceneObject.h"
#include "Button.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "Text.h"
#include "Brick.h"
#include "LevelGetter.h"

const float GameScene::border_left = Brick::getBrickPositionByCoordinates(0, 0)[0] - BRICK_WX / 2;
const float GameScene::border_right = Brick::getBrickPositionByCoordinates(BRICKS_X - 1, 0)[0] + BRICK_WX / 2;
const float GameScene::zone_down = RY - 30.0f;

GameScene::GameScene(int _level)
	: level(_level),
	border_up(Brick::getBrickPositionByCoordinates(0, 0)[1] - BRICK_WY / 2)
{
	// --- Create game objects ---

	// level number info text
	wstring level_text = (level + 1) < 10 ? L"0" : L"";
	level_text += to_wstring(level + 1) + L" / " + to_wstring(LEVELS);
	level_num_text = dynamic_cast<Text*>(addObject(new Text(
		RX - 140, 50, level_text, 70
	)));

	// plate
	plate = dynamic_cast<Plate*>(addObject(new Plate(
		RX / 2, RY - 30.0f, border_left, border_right, 2
	)));

	// walls
	createDecorationWalls();

	// grid
	populateGrid(level);

	// spawn a lot of balls
	for (int i = 2; i < 5; i++)
	{
		Ball* ball = new Ball(CX, CY, 0, 0);
		addObject(ball);
		balls.push_back(ball);
		ball->setVelocityByAngle(i * 15, 50);
	}

	// --- Create game UI ---
	sf::Color pause_color(60, 60, 60, 180);
	sf::Color win_color(0, 100, 0, 180);
	sf::Color defeat_color(100, 0, 0, 180);
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
		addObject(new Text(CPX1, CPY1 - 175, L"PAUSE", 190, sf::Color::Black)), // pause text
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
	
	// Sound initialization
	Sound::init();
	Sound::setGlobalVolume(80.f);
	Sound::playMusic("1");
}

GameScene::~GameScene()
{
	// Disable pause after leaving game scene
	input_data->game_window->setPause(false);
}

void GameScene::sceneUpdate(float delta_time)
{
	// Event flags
	bool end_now = false;
	bool pause_now = false;
	bool win_now = false;

	// Scene event handling
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

	// Whole level movement (every brick_fall_time miliseconds)
	if (fall_time_counter >= brick_fall_time / 1000.0f)
	{
		moveDownEverything(BRICK_WY / 3, true);
		fall_time_counter -= brick_fall_time / 1000.0f;
		brick_falls_done++;
	}

	// Ball movement (physics will be implemented here or something like that)
	for (Ball* ball : balls)
	{
		ball->step(delta_time);
	}

	// Ball position checking and destroying them
	vector <Ball*> balls_to_remove = {};
	for (Ball* ball : balls)
	{
		if (ball->getPosition()[1] > zone_down) // destroy condition
		{
			markToDelete(ball);
			balls_to_remove.push_back(ball);
		}
	}
	for (Ball* ball_rem : balls_to_remove) // cleaning balls from vector
	{
		balls.erase(
			std::remove(balls.begin(), balls.end(), ball_rem),
			balls.end()
		);
	}
	if (balls.size() == 0) // end game if no balls on scene
		end_now = true;

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

	// Past set
	fall_time_counter += delta_time;
	was_click_left_pressed = input_data->click_left;
	was_escape_pressed = input_data->escape;
	local_screen_before = local_screen;
}

void GameScene::createDecorationWalls()
{
	const float SIZE_MARGIN = 2000.0f;
	const sf::Color bg_color = sf::Color(150, 150, 150);
	const sf::Color zone_color = sf::Color(120, 120, 120);
	const sf::Color wall_color = sf::Color(60, 60, 60);
	const sf::Color bg_up_color = sf::Color(80, 80, 80);
	const sf::Color cont_color = sf::Color(20, 20, 20);

	// Background
	addObject(new Rectangle(
		0, 0,
		SIZE_MARGIN, SIZE_MARGIN,
		0,
		bg_color,
		sf::Color::Black,
		-10
	));

	// Down background strip
	addObject(new Rectangle(
		0, RY,
		SIZE_MARGIN, 2 * (RY - zone_down),
		0,
		zone_color,
		sf::Color::Black,
		-9
	));

	// Wall left
	addObject(new Rectangle(
		border_left - SIZE_MARGIN / 2, 0,
		SIZE_MARGIN, SIZE_MARGIN,
		10,
		wall_color,
		cont_color,
		16
	));

	// Wall right
	addObject(new Rectangle(
		border_right + SIZE_MARGIN / 2, 0,
		SIZE_MARGIN, SIZE_MARGIN,
		10,
		wall_color,
		cont_color,
		16
	));

	// Wall up
	crusher = dynamic_cast<Rectangle*>(addObject(new Rectangle(
		0, border_up - SIZE_MARGIN / 2,
		SIZE_MARGIN, SIZE_MARGIN,
		10,
		bg_up_color,
		cont_color,
		15
	)));
}

void GameScene::populateGrid(int level_id)
{
	// Level load
	const LevelData level_data = LevelGetter::getLevel(level_id);
	if (level >= 0) // if not endless
	{
		brick_fall_time = level_data.brick_fall_time;
		ball_max_speed = level_data.ball_max_speed;
	}

	// Populate with bricks
	for (int x = 0; x < BRICKS_X; x++)
		for (int y = 0; y < BRICKS_Y; y++)
		{
			char brick_id = level_data.brick_table[x][y];
			if (brick_id == '.')
				continue;

			auto brick_pos = Brick::getBrickPositionByCoordinates(x, y);
			float put_x = brick_pos[0];
			float put_y = brick_pos[1] + grid_populate_delta_y;
			Brick* put_brick = nullptr;

			if (brick_id >= '1' && brick_id <= '4')
				put_brick = new Brick(put_x, put_y, brick_id - '0');

			else throw runtime_error("Unknown brick type!");
			
			addObject(put_brick);
			bricks.push_back(put_brick);
		}

	// Next time must spawn tiles higher
	grid_populate_delta_y -= BRICKS_Y * BRICK_WY;
}

void GameScene::moveDownEverything(float delta_y, bool with_crusher)
{
	// Crusher movement
	if (with_crusher)
	{
		auto crusher_pos0 = crusher->getPosition();
		crusher->setPosition(crusher_pos0[0], crusher_pos0[1] + delta_y);
		border_up += delta_y; // also change upper border
	}

	// Brick movement
	for (Brick* brick : bricks)
	{
		auto pos0 = brick->getPosition();
		brick->setPosition(pos0[0], pos0[1] + delta_y);
	}

	// Populate variable change (should populate lower when lowering map)
	grid_populate_delta_y += delta_y;
}
