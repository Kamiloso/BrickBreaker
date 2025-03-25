#include "GameWindow.h"
#include "Scene.h"
#include "SceneObject.h"

GameWindow::GameWindow(string _title, sf::ContextSettings _settings)
{
	title = _title;
	settings = _settings;
	makeWindow(fullscreen);

	scenes.push_back(new Scene()); // ID = 0 : : Main Menu
	scenes.push_back(new Scene()); // ID = 1 : : Level Menu
	scenes.push_back(new Scene()); // ID = 2 : : Game Scene

	scenes[0]->addObject(new TempCircle(200, 200, 60, sf::Color::Magenta));
	scenes[1]->addObject(new TempCircle(RX / 2, RY / 2, 100, sf::Color::Red));
	scenes[2]->addObject(new TempCircle(RX - 200, RY - 200, 140, sf::Color::Cyan));
}

GameWindow::~GameWindow()
{
	for (Scene* scene : scenes)
		delete scene;
}

void GameWindow::run()
{
	while (true) {
		eventHandling();
		if (!window.isOpen()) {
			//saveAllNow();
			break;
		}
		update();
		render();
		//std::this_thread::sleep_for(std::chrono::milliseconds(500)); // VERY TEMPORARY!!!
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

void GameWindow::setScene(size_t scene_id)
{
	if (current_scene >= 0 && current_scene < scenes.size())
		current_scene = scene_id;
	else
		throw invalid_argument("Wrong scene ID");
}

size_t GameWindow::getScene() const
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

			if (event.key.code == sf::Keyboard::Space)
			{
				if (getScene() != 2)
					setScene(getScene() + 1);
				else
					setScene(0);
			}
		}
	}
}

void GameWindow::update()
{
	
}

void GameWindow::render()
{
	// Clear window
	window.clear(sf::Color(100, 100, 100)); // Gray

	// Render scene
	scenes[current_scene]->drawScene(this);

	// Safety resolution bars
	drawRectangle(-2000, 0, 4000, 9999, sf::Color::Black);
	drawRectangle(RX + 2000, 0, 4000, 9999, sf::Color::Black);
	drawRectangle(0, -2000, 9999, 4000, sf::Color::Black);
	drawRectangle(0, RY + 2000, 9999, 4000, sf::Color::Black);

	window.display();
}
