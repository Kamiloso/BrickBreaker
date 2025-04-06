#pragma once
#include "SceneObject.h"
class Collider : public SceneObject
{

	float wx;
	float wy;
	float left_border;
	float right_border;
	sf::Color color;
public:
	Collider(float _x,float _y,float _wx,float _wy,float _left_border,float _right_border,sf::Color _color,int _layer);
	void draw(GameWindow* game_window) override;
	void earlyUpdate(float delta_time) override;
};

