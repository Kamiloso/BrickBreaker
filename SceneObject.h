#pragma once

#include <SFML/Graphics.hpp>

class GameWindow;

using namespace std;

class SceneObject
{
public:
	SceneObject(float _x, float _y, float _rot) : x(_x), y(_y), rot(_rot) {}
	virtual ~SceneObject() {}
	virtual void draw(GameWindow* game_window) {}
	virtual void update(float delta_time) {}
	virtual int getEvent() { return 0; }

protected:
	float x, y, rot;
};

class TempCircle : public SceneObject
{
public:
	TempCircle(float _x, float _y, float _r, sf::Color _color) : SceneObject(_x, _y, 0), r(_r), color(_color) {}
	void draw(GameWindow* game_window) override;
	void update(float delta_time) override;
	int getEvent() override;

protected:
	float r;
	sf::Color color;
};
