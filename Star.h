#pragma once
#include "SceneObject.h"
#include <random>
using namespace std;

class Rectangle;

class Star: public SceneObject
{
public:
	Star(float _x, float _y, float _r, mt19937* gen, int _layer = 1);
	void draw(GameWindow* game_window) override;
	void lateUpdate(float delta_time);
	bool centerInRect(Rectangle* rect); // checks if overlaps with a virtual rect
private:
	float r;
	float opacity_time;
	sf::Color color;
	float phase;
};

