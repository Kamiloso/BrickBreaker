#pragma once

#include <SFML/Graphics.hpp>

class GameWindow;
struct InputData;

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

	bool isVisible() const { return visible;  } // should be drawn?
	void setVisible(bool _visible) { visible = _visible; } // change visibility state

	vector<float> getPosition() const;
	virtual void setPosition(float _x, float _y);
	float getRotation() const;
	virtual void setRotation(float _rot);

	const int layer;

protected:
	float x, y, rot;

private:
	bool visible = true;
};
