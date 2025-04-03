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

void SceneObject::updateInputData(const InputData* _input_data)
{
	input_data = _input_data;
}

void TempCircle::draw(GameWindow* game_window)
{
	game_window->drawCircle(x, y, r, sf::Color::Black);
	game_window->drawCircle(x, y, r - 20, color);
}

void TempCircle::earlyUpdate(float delta_time)
{
	// here you can do something right before sceneUpdate(), for example
	// it is the last moment to access data from the last frame

	float last_x = x;
	float last_y = y;
}

void TempCircle::lateUpdate(float delta_time)
{
	// it executes right after sceneUpdate() and is a good place to
	// update graphics, as rendering starts right after execution of it

	static unsigned char static_color_modifier = 0;
	static_color_modifier++;
	color = sf::Color(static_color_modifier, static_color_modifier + 100, static_color_modifier + 200);
}

int TempCircle::getEvent()
{
	if (x >= RX)
		return 1;
	else
		return 0;
}

int TempCircle::getEventToScene()
{
	if (x >= RX - 200)
		return 1;
	else
		return 0;
}

void TempCircle::step(float delta_time)
{
	x += delta_time * 100;
}
