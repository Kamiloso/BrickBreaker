#pragma once

#include "SceneObject.h"

// ------------------------------||
// The basic circle scene object ||
// ------------------------------||

class Circle : public SceneObject
{
public:
	Circle(float _x, float _y, float _r, float _bold, sf::Color _color, sf::Color _color_bold = sf::Color::Black, int _layer = 0);
	void draw(GameWindow* game_window) override;

protected:
	float r;
	float bold;
	sf::Color color;
	sf::Color color_bold;
};