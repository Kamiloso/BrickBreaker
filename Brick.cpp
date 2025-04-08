#include "Brick.h"

Brick::Brick(float _x, float _y, float _wx, float _wy, sf::Color brick_color, sf::Color border_color, int _layer)
:Rectangle(_x,_y,_wx,_wy,0,brick_color,border_color,_layer){}
