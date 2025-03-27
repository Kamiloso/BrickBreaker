#pragma once

#include "SceneObject.h"

// ---------------------------------||
// The basic rectangle scene object ||
// ---------------------------------||

class Rectangle : public SceneObject
{
public:
	Rectangle(float _x, float _y, float _wx, float _wy, float _bold, sf::Color _color, sf::Color _color_bold = sf::Color::Black);
	void draw(GameWindow* game_window) override;

protected:
	float wx;
	float wy;
	float bold;
	sf::Color color;
	sf::Color color_bold;
};