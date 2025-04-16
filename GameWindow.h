#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <unordered_set>

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
	void setPause(bool enable); // sets pause state to true or false

	// Getters
	bool isPause() const;
	int getScene() const;

	const sf::Vector2u small_resolution = { RX,RY };
	const sf::VideoMode big_resolution = sf::VideoMode::getFullscreenModes()[0];
	const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

private:

	sf::RenderWindow window;
	sf::ContextSettings settings;

	string title = "";
	bool fullscreen = true;
	bool game_pause = false;

	Scene* scene = nullptr;
	int current_scene = 0;

	unordered_set<sf::Keyboard::Key> key_storage; // stores currently pressed keyboard keys
	unordered_set<sf::Mouse::Button> mouse_storage; // stores currently pressed mouse buttons

	void makeWindow(bool full); // Creates or recreates window
	void setScene(int scene_id, int parameter = 0); // Sets scene (use only in events)

	void eventHandling(); // Handles events
	void update(float delta_time); // Runs game logic
	void render(); // Renders graphics
};
