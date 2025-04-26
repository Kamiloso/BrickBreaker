#pragma once
#include <SFML/Graphics.hpp>
// DO NOT IMPORT OUR PRIVATE DEPENDENCIES

/*
This header is not meant to be connected to any .cpp file. It stores global essentials and
constants for the project.
*/

// UNIVERSAL CONSTANTS
constexpr float PI = 3.14159265;	// PI - the famous number

// SCREEN CONSTANTS
constexpr int RX = 1280;	// physical screen width (not resolution)
constexpr int RY = 720;		// physical screen height (not resolution)
constexpr int CX = RX / 2;  // screen middle
constexpr int CY = RY / 2;  // screen middle

// MENU CONSTANTS
constexpr int LEVELS = 40;	// amount of levels

// GAMEPLAY CONSTANTS
constexpr int BRICKS_X = 7;		// how many bricks there can be horizontally
constexpr int BRICKS_Y = 13;	// how many bricks there can be vertically
constexpr float BRICK_WX = 100;	// brick size in x coordinates
constexpr float BRICK_WY = 50;	// brick size in y coordinates

// COLORS
namespace COL
{
	// UI colors
	static const sf::Color buttonBold = sf::Color(30, 36, 107);
	static const sf::Color buttonBg = sf::Color(38, 226, 255);
	static const sf::Color levelComplete = sf::Color(38, 175, 255);
	static const sf::Color levelUnlocked = sf::Color(3, 252, 102);
	static const sf::Color buttonExit = sf::Color(240, 30, 30);
	static const sf::Color buttonExitBold = sf::Color(70, 0, 0);

	// Game colors
	static const sf::Color plate = sf::Color::Yellow;
	static const sf::Color reversedPlate = sf::Color(255, 193, 0);
	static const sf::Color ball = sf::Color::Green;
	static const sf::Color brick = sf::Color(230, 0, 0);
}
