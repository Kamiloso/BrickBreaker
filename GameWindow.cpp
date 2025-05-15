#include "GameWindow.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "GameScene.h"
#include "Input.h"
#include "Sound.h"

#include <random>

GameWindow::GameWindow(string _title, sf::ContextSettings _settings)
{
	title = _title;
	settings = _settings;
	Input::init(this);
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
	const float MAX_DELTA_TIME = 0.05f; // less then 20 FPS --> slow down the game

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

void GameWindow::drawRectangleWithTexture(float pos_x, float pos_y, float wx, float wy, const sf::Texture* texture)
{
	sf::RectangleShape shape({wx, wy});
	shape.setPosition(pos_x - wx / 2, pos_y - wy / 2);
	shape.setTexture(texture);
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

unsigned int GameWindow::getEntropy()
{
	static random_device rd;
	static mt19937 ms_twister(rd());
	return ms_twister();
}

void GameWindow::setScene(int scene_id, int parameter)
{
	delete scene; // ok even if scene is nullptr
	switch (scene_id)
	{
	case 0: // Main Menu
		scene = new MainMenu(parameter);
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
}

void GameWindow::windowClose()
{
	window.close();
	Sound::doSoundCleaning(true);
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
	// "Anytime" input vectors
	unordered_set<sf::Keyboard::Key> key_anytime; // stores pressed keyboard keys now
	unordered_set<sf::Mouse::Button> mouse_anytime; // stores pressed mouse buttons now

	// Window events
	sf::Event event;
	while (window.pollEvent(event))
	{
		// MOUSE
		if (event.type == sf::Event::MouseButtonPressed)
		{
			mouse_anytime.insert(event.mouseButton.button);
			mouse_storage.insert(event.mouseButton.button);
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			mouse_storage.erase(event.mouseButton.button);
		}

		// KEYS
		if (event.type == sf::Event::KeyPressed)
		{
			key_anytime.insert(event.key.code);
			key_storage.insert(event.key.code);
		}
		if (event.type == sf::Event::KeyReleased)
		{
			key_storage.erase(event.key.code);
		}

		// OTHER EVENTS
		if (event.type == sf::Event::Closed)
		{
			windowClose();
			return;
		}
	}

	// Input data update
	sf::Vector2i pixel_pos = sf::Mouse::getPosition(window); // Mouse position
	sf::Vector2f mouse_pos = window.mapPixelToCoords(pixel_pos); // Conversion to world coordinates

	key_anytime.insert(key_storage.begin(), key_storage.end());;
	mouse_anytime.insert(mouse_storage.begin(), mouse_storage.end());

	Input::frameUpdate(
		mouse_pos.x, mouse_pos.y,
		key_anytime, mouse_anytime
	);

	// Full screen instant-after change
	if (Input::isKeyboardPressed(sf::Keyboard::F11, Input::Down) ||
		Input::isKeyboardPressed(sf::Keyboard::F, Input::Down))
		makeWindow(!fullscreen);

	// Game events
	vector<int> scene_events = scene->getEvents();
	for (int& event_id : scene_events)
	{
		if (event_id == 1) // next scene
			setScene((getScene() + 1) % 3);

		else if(event_id == 2) // window close
			windowClose();

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
