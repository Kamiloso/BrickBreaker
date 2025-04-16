#pragma once
#include <vector>
#include <unordered_set>
#include <SFML/Graphics.hpp>

using namespace std;

class GameWindow;

class Input
{
public:
	// Enum
	enum PressMode {
		Down, Hold, Up
	};

	// Writing
	static void init(GameWindow* _game_window); // initializes input class with game window
	static void frameUpdate(
		float _mouse_x, float _mouse_y,
		unordered_set<sf::Keyboard::Key> _keyboard_clicked,
		unordered_set<sf::Mouse::Button> _mouse_clicked
	); // updates the input list (executes in eventHandling)

	// Reading
	static GameWindow* getGameWindowPtr();
	static vector<float> getMousePosition(); // returns vector of two floats: {x,y}
	static bool isKeyboardPressed(sf::Keyboard::Key key, PressMode mode = Hold);
	static bool isMousePressed(sf::Mouse::Button mkey, PressMode mode = Hold);

private:
	static GameWindow* game_window;
	static float mouse_x, mouse_y;
	static unordered_set<sf::Keyboard::Key> keyboard_hold;
	static unordered_set<sf::Keyboard::Key> keyboard_down;
	static unordered_set<sf::Keyboard::Key> keyboard_up;
	static unordered_set<sf::Mouse::Button> mouse_hold;
	static unordered_set<sf::Mouse::Button> mouse_down;
	static unordered_set<sf::Mouse::Button> mouse_up;
};
