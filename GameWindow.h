#pragma once
#include <vector>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include "common.h"

class Scene;

using namespace std;

// ----------------------------------------------------------------||
// The main class, that manages the whole game and window settings ||
// ----------------------------------------------------------------||

class GameWindow final
{
public:
	GameWindow(string _title, sf::ContextSettings _settings);
	~GameWindow();

	void run(); // Starts main game loop
	void drawCircle(float pos_x, float pos_y, float r, sf::Color color);
	void drawRectangle(float pox_x, float pos_y, float wx, float wy, sf::Color color);
	sf::RenderWindow& getRenderWindow(); // returns 'window' reference for drawing more complex shapes
	static sf::Font& getFont(); // returns game font
	int getScene() const;

	const sf::Vector2u small_resolution = { RX,RY };
	const sf::VideoMode big_resolution = sf::VideoMode::getFullscreenModes()[0];
	const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

private:

	sf::RenderWindow window;
	sf::ContextSettings settings;

	string title = "";
	bool fullscreen = true;

	Scene* scene = nullptr;
	int last_frame_scene = -1;
	int current_scene = 0;

	void makeWindow(bool full); // Creates or recreates window
	void setScene(int scene_id); // Sets scene (use only in events)

	void eventHandling(); // Handles events
	void update(float delta_time); // Runs game logic
	void render(); // Renders graphics
};

