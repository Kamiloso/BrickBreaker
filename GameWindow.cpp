#include "GameWindow.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "GameScene.h"

GameWindow::GameWindow(string _title, sf::ContextSettings _settings)
{
	title = _title;
	settings = _settings;
	makeWindow(fullscreen);
	setScene(0);
}

GameWindow::~GameWindow()
{
	delete scene;
}

void GameWindow::run()
{
	sf::Clock clock;
	float delta_time = 0.0f;
	const float MAX_DELTA_TIME = 0.1f; // less then 10 FPS --> slow down the game

	while (true)
	{
		eventHandling(); // handle window & game events
		if (!window.isOpen())
			break;

		delta_time = clock.restart().asSeconds();

		if (delta_time > MAX_DELTA_TIME) // anti-bar-hold-pause
			delta_time = MAX_DELTA_TIME;

		if (game_pause)
			delta_time = 0.0f;

		update(delta_time); // update game logic
		render(); // render screen

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void GameWindow::drawCircle(float pos_x, float pos_y, float r, sf::Color color)
{
	sf::CircleShape shape(r);
	shape.setPosition(pos_x - r, pos_y - r);
	shape.setFillColor(color);
	window.draw(shape);
}

void GameWindow::drawRectangle(float pos_x, float pos_y, float wx, float wy, sf::Color color)
{
	sf::RectangleShape shape({ wx, wy });
	shape.setPosition(pos_x - wx / 2, pos_y - wy / 2);
	shape.setFillColor(color);
	window.draw(shape);
}

sf::RenderWindow& GameWindow::getRenderWindow()
{
	return window;
}

void GameWindow::setPause(bool enable)
{
	game_pause = enable;
}

void GameWindow::setScene(int scene_id, int parameter)
{
	delete scene; // ok even if scene is nullptr
	switch (scene_id)
	{
	case 0: // Main Menu
		scene = new MainMenu();
		break;
	case 1: // Level Menu
		scene = new LevelMenu();
		break;
	case 2: // Game Scene
		scene = new GameScene(parameter);
		break;
	default:
		throw std::invalid_argument("Invalid scene ID");
	}
	current_scene = scene_id;
	scene->inputPropagate(&main_input_data); // propagate input pointer to scene
}

bool GameWindow::isPause() const
{
	return game_pause;
}

int GameWindow::getScene() const
{
	return current_scene;
}

void GameWindow::makeWindow(bool full)
{
	fullscreen = full;
	if (fullscreen)
	{
		window.create(sf::VideoMode(big_resolution.width, big_resolution.height), title, sf::Style::Fullscreen, settings);
		
		float ratio_small = (small_resolution.x * 1.0) / small_resolution.y;
		float ratio_big = (big_resolution.width * 1.0) / big_resolution.height;
		
		if (ratio_big < ratio_small) // X is fixed
		{
			window.setView(sf::View(sf::FloatRect(
				0,
				-(small_resolution.x / ratio_big - small_resolution.y) / 2,
				small_resolution.x,
				small_resolution.x / ratio_big
			)));
		}
		else // Y is fixed
		{
			window.setView(sf::View(sf::FloatRect(
				-(small_resolution.y * ratio_big - small_resolution.x) / 2,
				0,
				small_resolution.y * ratio_big,
				small_resolution.y
			)));
		}
	}
	else
	{
		window.create(sf::VideoMode(small_resolution.x, small_resolution.y), title, sf::Style::Close, settings);
		window.setView(sf::View(sf::FloatRect(0, 0, small_resolution.x, small_resolution.y)));
		window.setPosition(sf::Vector2i(
			(desktop.width - small_resolution.x) / 2,
			(desktop.height - small_resolution.y) / 2
		));
	}
	window.setVerticalSyncEnabled(true);
}

void GameWindow::eventHandling()
{
	// Anytime input reset
	main_input_data.click_left_start = false;
	main_input_data.escape_start = false;

	// Window events
	sf::Event event;
	while (window.pollEvent(event))
	{
		// MOUSE
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				main_input_data.click_left_start = true;
				main_input_data.click_left_now = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				main_input_data.click_left_now = false;
			}
		}

		// KEYS
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::F11 || event.key.code == sf::Keyboard::F)
			{
				makeWindow(!fullscreen);
			}

			if (event.key.code == sf::Keyboard::Escape)
			{
				main_input_data.escape_start = true;
				main_input_data.escape_now = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				main_input_data.escape_now = false;
			}
		}

		// OTHER EVENTS
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return;
		}
	}

	// Input to send
	sf::Vector2i pixel_pos = sf::Mouse::getPosition(window); // Mouse position
	sf::Vector2f mouse_pos = window.mapPixelToCoords(pixel_pos); // Conversion to world coordinates
	main_input_data.mouse_x = mouse_pos.x;
	main_input_data.mouse_y = mouse_pos.y;
	main_input_data.click_left = main_input_data.click_left_start || main_input_data.click_left_now;
	main_input_data.escape = main_input_data.escape_start || main_input_data.escape_now;
	main_input_data.game_window = this; // Game window reference add

	// Game events
	vector<int> scene_events = scene->getEvents();
	for (int& event_id : scene_events)
	{
		if (event_id == 1) // next scene
			setScene((getScene() + 1) % 3);

		else if(event_id == 2) // window close
			window.close();

		else if (event_id >= 1000 && event_id < 1999) // set scene by ID
			setScene(event_id - 1000);

		else if (event_id >= 2000 && event_id < 2999) // set menu scene with parameter (local screen)
			setScene(0, event_id - 2000);

		else if (event_id >= 3000 && event_id < 3999) // set game scene with parameter (level ID)
			setScene(2, event_id - 3000);

		else throw exception("Invalid event ID");
	}
}

void GameWindow::update(float delta_time)
{
	scene->update(delta_time); // I think it may be ok
}

void GameWindow::render()
{
	// Clear window
	window.clear(sf::Color(100, 100, 100)); // gray

	// Render scene
	scene->drawScene(this);

	// Safety resolution bars
	drawRectangle(-2000, 0, 4000, 9999, sf::Color::Black);
	drawRectangle(RX + 2000, 0, 4000, 9999, sf::Color::Black);
	drawRectangle(0, -2000, 9999, 4000, sf::Color::Black);
	drawRectangle(0, RY + 2000, 9999, 4000, sf::Color::Black);

	window.display();
}
