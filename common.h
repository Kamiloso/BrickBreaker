#pragma once
#include <SFML/Graphics.hpp>
// DO NOT IMPORT OUR PRIVATE DEPENDENCIES

class GameWindow;

/*
This header is not meant to be connected to any .cpp file. It stores global essentials and
constants for the project.
*/

// SCREEN CONSTANTS
constexpr int RX = 1280;	// physical screen width (not resolution)
constexpr int RY = 720;		// physical screen height (not resolution)
constexpr int CX = RX / 2;  // screen middle
constexpr int CY = RY / 2;  // screen middle

// GAMEPLAY CONSTANTS
constexpr int BRICKS_X = 7;		// how many bricks there can be horizontally
constexpr int BRICKS_Y = 13;	// how many bricks there can be vertically
constexpr float BRICK_WX = 100;	// brick size in x coordinates
constexpr float BRICK_WY = 50;	// brick size in y coordinates

// MENU CONSTANTS
constexpr int LEVELS = 40;	// amount of levels

// COLORS
namespace COL
{
	static const sf::Color buttonBold = sf::Color(30, 36, 107);
	static const sf::Color buttonBg = sf::Color(38, 226, 255);
	static const sf::Color levelComplete = sf::Color(38, 175, 255);
	static const sf::Color levelUnlocked = sf::Color(3, 252, 102);
}

// DATA STRUCTURES
struct InputData
{
public:
	float mouse_x = 0.0f; // mouse x position
	float mouse_y = 0.0f; // mouse y position
	bool click_left = false; // is left button clicked?
	bool escape = false; // is escape clicked?

	GameWindow* game_window = nullptr; // Not exactly input, but allows for easy access to game window

private: // no, you don't know how this thing below works, so don't try to use it
	bool click_left_start = false;
	bool click_left_now = false;
	bool escape_start = false;
	bool escape_now = false;

	friend GameWindow;
};
