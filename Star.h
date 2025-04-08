#pragma once
#include "SceneObject.h"
#include <random>
using namespace std;

class Star: public SceneObject
{
public:
	Star(float _x, float _y, float _r, mt19937* _gen, int _layer = 1);
	void draw(GameWindow* game_window) override;
	void lateUpdate(float delta_time);
private:
	float r;
	float opacity_time;
	mt19937* gen;
	sf::Color color;
	float phase;
};

