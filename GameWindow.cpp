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

	while (true)
	{
		eventHandling(); // handle window & game events
		if (!window.isOpen()) {
			//saveAllNow();
			break;
		}
		delta_time = clock.restart().asSeconds();
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

void GameWindow::setScene(int scene_id)
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
		scene = new GameScene();
		break;
	default:
		throw std::invalid_argument("Invalid scene ID");
	}
	current_scene = scene_id;
	scene->inputPropagate(&main_input_data); // propagate input pointer to scene
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
	main_input_data.space_start = false;

	// Window events
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return;
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				return;
			}
			
			if (event.key.code == sf::Keyboard::F11 || event.key.code == sf::Keyboard::F)
			{
				makeWindow(!fullscreen);
			}

			// From there input send things

			if (event.key.code == sf::Keyboard::Space)
			{
				main_input_data.space_start = true;
				main_input_data.space_now = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				main_input_data.space_now = false;
			}
		}
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
	}

	// Input to send
	sf::Vector2i pixel_pos = sf::Mouse::getPosition(window); // Mouse position
	sf::Vector2f mouse_pos = window.mapPixelToCoords(pixel_pos); // Conversion to world coordinates
	main_input_data.mouse_x = mouse_pos.x;
	main_input_data.mouse_y = mouse_pos.y;
	main_input_data.click_left = main_input_data.click_left_start || main_input_data.click_left_now;
	main_input_data.space = main_input_data.space_start || main_input_data.space_now;

	// Game events
	vector<int> scene_events = scene->getEvents();
	for (int& event_id : scene_events)
	{
		switch (event_id)
		{
		case 1: // next scene
			setScene((getScene() + 1) % 3);
			return;

		case 2: // quit
			window.close();
			return;

		case 1000: // jump to scene
		case 1001:
		case 1002:
			setScene(event_id - 1000);
			return;

		default:
			throw exception("Invalid event ID");
		}
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
