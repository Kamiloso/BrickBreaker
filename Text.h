#pragma once
#include <string>

#include "SceneObject.h"

using namespace std;

// -----------------------------------||
// Text class for simple text display ||
// -----------------------------------||

class Text : public SceneObject
{
public:
	Text(float _x, float _y, const wstring& _text, float _font, sf::Color _color = sf::Color::Black, int _layer = 25);
	void draw(GameWindow* game_window) override;

protected:
	wstring text;
	float font;
	sf::Color color;
};