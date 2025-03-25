#pragma once

#include <SFML/Graphics.hpp>

class GameWindow;

using namespace std;

class SceneObject
{
public:
	SceneObject(float _x, float _y, float _rot) : x(_x), y(_y), rot(_rot) {}
	virtual void draw(GameWindow* game_window) {};

protected:
	float x, y, rot;
};

class TempCircle : public SceneObject
{
public:
	TempCircle(float _x, float _y, float _r, sf::Color _color) : SceneObject(_x, _y, 0), r(_r), color(_color) {}
	void draw(GameWindow* game_window) override;

protected:
	float r;
	sf::Color color;
};
