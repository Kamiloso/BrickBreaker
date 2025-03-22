#include "GameWindow.h"

GameWindow::GameWindow(string _title, sf::ContextSettings _settings)
{
	title = _title;
	settings = _settings;
	makeWindow(fullscreen);
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
		window.create(sf::VideoMode(small_resolution.x, small_resolution.y), title, sf::Style::Close);
		window.setView(sf::View(sf::FloatRect(0, 0, small_resolution.x, small_resolution.y)));
		window.setPosition(sf::Vector2i(
			(desktop.width - small_resolution.x) / 2,
			(desktop.height - small_resolution.y) / 2
		));
	}
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
		}
	}
}

void GameWindow::update()
{

}

void GameWindow::render()
{
	const int LX = small_resolution.x;
	const int LY = small_resolution.y;

	window.clear(sf::Color::White);

	// Circle tests
	for (int i = 50; i < LX; i += 100)
	{
		for (int j = 50; j < LY; j += 100)
		{
			drawCircle(i, j, 35, sf::Color::Blue);
		}
	}

	// Safety resolution bars
	drawRectangle(-2000, 0, 4000, 9999);
	drawRectangle(LX + 2000, 0, 4000, 9999);
	drawRectangle(0, -2000, 9999, 4000);
	drawRectangle(0, LY + 2000, 9999, 4000);

	window.display();
}
