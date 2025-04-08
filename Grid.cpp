#include "Grid.h"
#include "GameWindow.h"

Grid::Grid(float _x,float _y,float _wx, float _wy, int _rows,int _cols,float _layer)
	:SceneObject(_x, _y, _layer), wx(_wx), wy(_wy), brickw(_wx / _cols), brickh(_wy / _rows), rows(_rows), cols(_cols)
{
	fillGrid();
}
void Grid::fillGrid()
{
	for (size_t col = 1; col <= cols; col++)
	{
		position_x.push_back(brickw* col);
	}
	for (size_t row = 1; row <= rows; row++)
	{
		position_y.push_back(brickh * row);
	}
}
