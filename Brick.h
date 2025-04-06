#pragma once
#include "Rectangle.h"
class Brick : public Rectangle
{
public:
	Brick(float _x,float _y,float _wx,float _wy,sf::Color brick_color,sf::Color border_color,int _layer);
protected:

};

