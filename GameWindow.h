#pragma once
#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>
#include "common.h"

class Scene;

using namespace std;

class GameWindow
{
public:
	GameWindow(string _title, sf::ContextSettings _settings);
	~GameWindow();

	void run(); // Starts main game loop
	void drawCircle(float pos_x, float pos_y, float r, sf::Color color);
	void drawRectangle(float pox_x, float pos_y, float wx, float wy, sf::Color color);

	void setScene(size_t scene_id); size_t getScene() const; // scene changing

	const sf::Vector2u small_resolution = { RX,RY };
	const sf::VideoMode big_resolution = sf::VideoMode::getFullscreenModes()[0];
	const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

private:

	sf::RenderWindow window;
	sf::ContextSettings settings;

	string title = "";
	bool fullscreen = true;

	vector<Scene*> scenes;
	int current_scene = 0;

	void makeWindow(bool full); // Creates or recreates window
	void eventHandling(); // Handles window events
	void update(); // Runs game logic
	void render(); // Renders graphics
};

