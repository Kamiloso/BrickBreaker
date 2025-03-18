#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class GameWindow
{
public:
	GameWindow(string _title, sf::ContextSettings _settings);

	void run(); // Starts main game loop
	void drawCircle(float pos_x, float pos_y, float r, sf::Color color = sf::Color::Black);
	void drawRectangle(float pox_x, float pos_y, float wx, float wy, sf::Color color = sf::Color::Black);

private:
	const sf::Vector2u small_resolution = { 1280,720 };
	const sf::VideoMode big_resolution = sf::VideoMode::getFullscreenModes()[0];
	const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	string title = "";
	bool fullscreen = false;
	sf::RenderWindow window;
	sf::ContextSettings settings;

	void setFullScreen(bool full);

	void eventHandling(); // Handles window events
	void update(); // Runs game logic
	void render(); // Renders graphics
};

