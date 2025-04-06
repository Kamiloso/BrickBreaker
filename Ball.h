#pragma once

#include "SceneObject.h"
#include <vector>
class Ball : public SceneObject
{
public:
	Ball(float pos_x, float pos_y, float _r, sf::Color _color,int _layer);
	void draw(GameWindow* game_window) override;
	int getEventToScene();
	void step(float delta_time);
protected:
	float vx = 0;
	float vy = 200;
	float r;
	sf::Color color;
};

