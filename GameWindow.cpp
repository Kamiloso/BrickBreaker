#include "GameWindow.h"
GameWindow::GameWindow(int resolution, string title)
	:window(sf::VideoMode(full_screen_resolutions[0].width, full_screen_resolutions[0].height), title, sf::Style::Fullscreen) {
	current_resolution = resolution;
}

void GameWindow::run()
{
	while (window.isOpen()) {
		eventHandling();
		update();
		render();
	}
}

void GameWindow::centerWindow()
{
	int x_position = ((desktop.width - resolutions[current_resolution].x) / 2);
	int y_position = ((desktop.height - resolutions[current_resolution].y) / 2);

	window.setPosition(sf::Vector2i(x_position, y_position));
}

void GameWindow::drawCircle()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(0, 0);
	window.draw(shape);
}

void GameWindow::setView()
{
	sf::View view(sf::FloatRect(0, 0, resolutions[current_resolution].x, resolutions[current_resolution].y));
	window.setView(view);
}

void GameWindow::eventHandling()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
			window.close();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
			current_resolution = 0;
			if (!fullscreen)
			{
				window.setSize(resolutions[current_resolution]);
				centerWindow();
			}
			setView();

		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
			current_resolution = 1;
			if (!fullscreen)
			{
				window.setSize(resolutions[current_resolution]);
				centerWindow();
			}
			setView();


		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3)) {
			current_resolution = 2;
			if (!fullscreen)
			{
				window.setSize(resolutions[current_resolution]);
				centerWindow();
			}
			setView();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F)) {
			fullscreen = !fullscreen;
			if (fullscreen==true)
			{
				window.create(sf::VideoMode(full_screen_resolutions[0].width, full_screen_resolutions[0].height), "fullscreen", sf::Style::Fullscreen);
			}
			if (fullscreen==false)
			{
				window.create(sf::VideoMode(resolutions[current_resolution].x, resolutions[current_resolution].y), "okno", sf::Style::Close);
				centerWindow();
			}
		}
	}
}

void GameWindow::update()
{
}

void GameWindow::render()
{
	window.clear(sf::Color::Black);
	drawCircle();
	window.display();
}
