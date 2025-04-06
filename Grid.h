#pragma once
#include "SceneObject.h"
#include <vector>
#include "Brick.h"
class Grid : public SceneObject
{
public:
	Grid(float _x,float _y,float _wx, float _wy, int _rows,int _cols,float _layer);
	void fillGrid();
	vector<float> position_x;
	vector<float> position_y;
	float brickh;
	float brickw;
protected:
	float wx;
	float wy;

	int rows;
	int cols;

};

