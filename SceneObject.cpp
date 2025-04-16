#include "SceneObject.h"
#include "GameWindow.h"
#include "common.h"

vector<float> SceneObject::getPosition() const
{
	return vector<float>{x, y};
}

void SceneObject::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

float SceneObject::getRotation() const
{
	return rot;
}

void SceneObject::setRotation(float _rot)
{
	rot = _rot;
}
