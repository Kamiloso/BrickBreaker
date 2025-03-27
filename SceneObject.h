#pragma once

#include <SFML/Graphics.hpp>

class GameWindow;

using namespace std;

// --------------------------------------||
// The base class for every scene object ||
// --------------------------------------||

class SceneObject
{
public:
	SceneObject(float _x, float _y, int _layer = 0) : x(_x), y(_y), rot(0.0f), layer(_layer) {}
	virtual ~SceneObject() {}
	virtual void draw(GameWindow* game_window) {} // draws object on a screen
	virtual void earlyUpdate(float delta_time) {} // executes once a frame right before sceneUpdate()
	virtual void lateUpdate(float delta_time) {} // executes once a frame right after sceneUpdate()
	virtual int getEvent() { return 0; } // sends event to game window if necessary
	virtual int getEventToScene() { return 0; } // sends event to scene manager if necessary

	vector<float> getPosition() const;
	void setPosition(float _x, float _y);
	float getRotation() const;
	void setRotation(float _rot);

	const int layer;

protected:
	float x, y, rot;
};

// -------------------------------------------------------||
// Temporary class to demostrate some game loop mechanics ||
// -------------------------------------------------------||

class TempCircle : public SceneObject
{
public:
	TempCircle(float _x, float _y, float _r, sf::Color _color) : SceneObject(_x, _y), r(_r), color(_color) {}
	void draw(GameWindow* game_window) override;
	void earlyUpdate(float delta_time) override;
	void lateUpdate(float delta_time) override;
	int getEvent() override;
	int getEventToScene() override;

	void step(float delta_time);

protected:
	float r;
	sf::Color color;
};
