#include "GameScene.h"
#include "SceneObject.h"
#include "Button.h"
#include "Rectangle.h"
#include "GameWindow.h"
#include "Text.h"
#include "Brick.h"
#include "LevelGetter.h"
#include "Plate.h"
#include "Ball.h"
#include "Sound.h"
#include "Input.h"
#include "CircleCollider.h"
#include "LineCollider.h"

#include <limits>
#include <cmath>

constexpr float FALL_DELTA_Y = BRICK_WY / 3;

const float GameScene::border_left = Brick::getBrickPositionByCoordinates(0, 0)[0] - BRICK_WX / 2;
const float GameScene::border_right = Brick::getBrickPositionByCoordinates(BRICKS_X - 1, 0)[0] + BRICK_WX / 2;
const float GameScene::zone_down = RY - 30.0f;

GameScene::GameScene(int _level)
	: level(_level),
	border_up(Brick::getBrickPositionByCoordinates(0, 0)[1] - BRICK_WY / 2)
{
	initializeGame(); // spawns game objects
	initializeUI(); // spawns UI scene objects
	populateGrid(level); // populates scene with bricks and configures level settings
	
	Sound::playMusic("1");

	// spawn a lot of balls
	for (int i = 0; i < 36; i++)
	{
		Ball* ball = new Ball(CX, CY, 0, 0);
		addObject(ball);
		balls.push_back(ball);
		ball->setVelocityByAngle(i * 10, 300);
	}
}

GameScene::~GameScene()
{
	// Get rid of remaining colliders
	for (Collider* collider : colliders)
		delete collider;

	// Disable pause after leaving game scene
	Input::getGameWindowPtr()->setPause(false);
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

	// Whole level movement (every brick_fall_time miliseconds)
	if (fall_time_counter >= brick_fall_time / 1000.0f)
	{
		if (canMoveDownEverything(true))
		{
			moveDownEverything(true);
			fall_time_counter -= brick_fall_time / 1000.0f;
			brick_falls_done++;
		}
		else fall_time_counter = brick_fall_time / 1000.0f; // procrastinate untill possible
	}

	// Physics
	applyGravity(0.00f);
	handlePhysics(delta_time);

	// Ball position checking and destroying them
	vector <Ball*> balls_to_remove = {};
	for (Ball* ball : balls)
	{
		if (ball->getPosition()[1] > zone_down || ball->isMarkedAsTerminated()) // destroy condition
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
		Sound::playSound("1"); // ball break sound
	}
	if (balls.size() == 0) // end game if no balls on scene
		end_now = true;

	// Escape pause toggle
	if (Input::isKeyboardPressed(sf::Keyboard::Escape, Input::Down))
		pause_now = true;

	// Local screen decide
	if (end_now)
	{
		if (win_now)
		{
			local_screen = 2; // win
			if (level >= 0)
				LevelGetter::setLevelFlag(level, 1); // mark level as complete
		}
		else
		{
			local_screen = 3; // defeat
		}
		Sound::stopMusic();
	}
	else
	{
		if (pause_now)
		{
			if (local_screen == 0)
			{
				local_screen = 1; // pause
				Sound::pauseMusic();
			}
			else if (local_screen == 1)
			{
				local_screen = 0; // none
				Sound::resumeMusic();
			}
		}
	}

	// Local screen togglator
	if (local_screen_before != local_screen)
	{
		Input::getGameWindowPtr()->setPause(local_screen != 0);

		float delta_move = -10000.0f * (local_screen - local_screen_before);
		for (SceneObject* obj : pause_menu_objects)
		{
			auto pos0 = obj->getPosition();
			obj->setPosition(pos0[0] + delta_move, pos0[1]);
		}
	}

	// Past set
	fall_time_counter += delta_time;
	local_screen_before = local_screen;
}

void GameScene::initializeGame()
{
	// plate
	plate = dynamic_cast<Plate*>(addObject(new Plate(
		RX / 2, RY - 30.0f, border_left, border_right, 2
	)));

	// walls
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

	// Wall up (crusher)
	crusher = dynamic_cast<Rectangle*>(addObject(new Rectangle(
		0, border_up - SIZE_MARGIN / 2,
		SIZE_MARGIN, SIZE_MARGIN,
		10,
		bg_up_color,
		cont_color,
		15
	)));
}

void GameScene::initializeUI()
{
	// level number info text
	wstring level_text = (level + 1) < 10 ? L"0" : L"";
	level_text += to_wstring(level + 1) + L" / " + to_wstring(LEVELS);
	level_num_text = dynamic_cast<Text*>(addObject(new Text(
		RX - 140, 50, level_text, 70
	)));

	// --- movable UI ---
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
}

void GameScene::populateGrid(int level_id)
{
	// Level load
	const LevelData level_data = LevelGetter::getLevel(level_id);
	brick_fall_time = level_data.brick_fall_time;
	ball_max_speed = level_data.ball_max_speed;

	// Populate with bricks
	for (int x = 0; x < BRICKS_X; x++)
		for (int y = 0; y < BRICKS_Y; y++)
		{
			char brick_id = level_data.brick_table[x][y];
			if (brick_id == '.')
				continue;

			auto brick_pos = Brick::getBrickPositionByCoordinates(x, y);
			float put_x = brick_pos[0];
			float put_y = brick_pos[1];
			Brick* put_brick = nullptr;

			if (brick_id >= '1' && brick_id <= '4')
				put_brick = new Brick(put_x, put_y, brick_id - '0');

			else throw runtime_error("Unknown brick type!");
			
			addObject(put_brick);
			bricks[x][y] = put_brick;
		}

	// Update colliders after populating the grid
	updateColliders();
}

bool GameScene::canMoveDownEverything(bool with_crusher)
{
	// Construct rectangles table
	vector<Rectangle*> local_rectangles = {};
	local_rectangles.reserve(BRICKS_X * BRICKS_Y + with_crusher);

	for (int x = 0; x < BRICKS_X; x++)
		for (int y = 0; y < BRICKS_Y; y++)
		{
			Brick* brick = bricks[x][y];
			if (brick != nullptr)
			{
				local_rectangles.push_back(brick);
			}
		}
	if (with_crusher)
		local_rectangles.push_back(crusher);

	// Iterate through every rectangle:ball pair end check if can move
	for (Rectangle* rect : local_rectangles)
	{
		auto r_pos = rect->getPosition();
		auto r_siz = rect->getScale();

		r_pos[1] += FALL_DELTA_Y; // simulate fallen brick

		for (Ball* ball : balls)
		{
			auto b_pos = ball->getPosition();
			float r = ball->getRadius();

			float diff_on_x = abs(r_pos[0] - b_pos[0]) - (r_siz[0] / 2 + r);
			float diff_on_y = abs(r_pos[1] - b_pos[1]) - (r_siz[1] / 2 + r);

			if (diff_on_x <= 0.0f && diff_on_y <= 0.0f)
				return false;
		}
	}

	return true;
}

void GameScene::moveDownEverything(bool with_crusher)
{
	// Crusher movement
	if (with_crusher)
	{
		auto crusher_pos0 = crusher->getPosition();
		crusher->setPosition(crusher_pos0[0], crusher_pos0[1] + FALL_DELTA_Y);
		border_up += FALL_DELTA_Y; // also change upper border
	}

	// Brick movement
	for (int x = 0; x < BRICKS_X; x++)
		for (int y = 0; y < BRICKS_Y; y++)
		{
			Brick* brick = bricks[x][y];
			if (brick != nullptr)
			{
				auto pos0 = brick->getPosition();
				brick->setPosition(pos0[0], pos0[1] + FALL_DELTA_Y);
			}
		}

	// Update colliders after everything has moved
	updateColliders();
}

void GameScene::updateColliders()
{
	// Reset current array
	for (Collider* collider : colliders)
		delete collider;
	colliders.clear();

	// Declare static non-brick colliders (for example walls)
	colliders = {
		new LineCollider(border_left + BALL_RADIUS, -10000, border_left + BALL_RADIUS, 10000, LineCollider::Right), // left wall
		new LineCollider(border_right - BALL_RADIUS, -10000, border_right - BALL_RADIUS, 10000, LineCollider::Left), // right wall
		new LineCollider(-10000, border_up + BALL_RADIUS, 10000, border_up + BALL_RADIUS, LineCollider::Down), // crusher roof
	};

	// Create collider for each brick
	for (int x = 0; x < BRICKS_X; x++)
		for (int y = 0; y < BRICKS_Y; y++)
		{
			Brick* brick = bricks[x][y];
			if (brick != nullptr)
			{
				bool up = (y > 0) && (bricks[x][y - 1] == nullptr);
				bool down = (y == BRICKS_Y - 1) || (bricks[x][y + 1] == nullptr);

				#pragma warning(suppress: 6201) // it's surely safe
				bool left = (x > 0) && (bricks[x - 1][y] == nullptr);

				#pragma warning(suppress: 6201) // it's surely safe
				bool right = (x < BRICKS_X - 1) && (bricks[x + 1][y] == nullptr);

				auto new_colliders = brick->createNewColliders(up, down, left, right);
				colliders.insert(colliders.begin(), new_colliders.begin(), new_colliders.end());
			}
		}
}

void GameScene::applyGravity(float g)
{
	for (Ball* ball : balls)
	{
		auto vel0 = ball->getVelocity();
		ball->setVelocity(
			vel0[0],
			vel0[1] + g
		);
	}
}

void GameScene::handlePhysics(float delta_time)
{
	// Bounce balls
	for (Ball* ball : balls)
	{
		ball->changeTime(delta_time); // add available movement time
	}
	while (true)
	{
		// looking for ball with the least time to bounce
		Ball* best_ball = nullptr;
		Collider* best_collider = nullptr;
		float best_time_to_collision = std::numeric_limits<float>::infinity();

		for (Ball* ball : balls)
		{
			float time_left = ball->getTimeAvailable();
			if (time_left <= 0.0f)
				continue;

			Collider* collider = ball->bestFitCollider(colliders);
			float time_to_collision = collider != nullptr ? collider->getTimeToCollision(ball) : NO_COLLISION;
			if (time_to_collision > time_left)
				time_to_collision = NO_COLLISION;

			if (best_ball == nullptr || (time_to_collision != NO_COLLISION && time_to_collision < best_time_to_collision))
			{
				best_ball = ball;
				best_collider = collider;
				best_time_to_collision = time_to_collision;
			}
		}

		// if cannot find more balls that want to move, just go on
		if (best_ball == nullptr)
			break;

		// actual collision
		if (best_time_to_collision == NO_COLLISION)
		{
			best_ball->step(best_ball->getTimeAvailable());
			best_ball->resetTime();
		}
		else
		{
			best_ball->step(best_time_to_collision);
			best_ball->changeTime(-best_time_to_collision);

			// actions on a brick
			Brick* brick = best_collider->getBrick();

			if (brick == nullptr) // no-brick
			{
				best_collider->bounceBall(best_ball);
			}

			else if (true) // normal brick
			{
				best_collider->bounceBall(best_ball);
				brick->damage();
				if (brick->shouldBreak())
				{
					for (int x = 0; x < BRICKS_X; x++)
						for (int y = 0; y < BRICKS_Y; y++)
							if (bricks[x][y] == brick)
							{
								bricks[x][y] = nullptr;
								markToDelete(brick);
								updateColliders();
								goto break_brick_break_loop;
							}
				break_brick_break_loop:;
				}
			}
		}
	}
}
