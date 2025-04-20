#pragma once
#include "Circle.h"
#include <vector>

class Collider;

static constexpr float BALL_RADIUS = 12.0f; // constant ball radius source

class Ball : public Circle
{
public:
	Ball(float _x, float _y, float _vx, float _vy, int _layer = 12);
	void step(float time);

	void setVelocity(float _vx, float _vy);
	void setVelocityByAngle(float angle, float magnitude); // degrees
	vector<float> getVelocity() const;
	float getVelocityAngle() const;
	float getVelocityMagnitude() const;

	void resetTime(); // resets available time for movement
	void changeTime(float time); // changes available time for movement
	float getTimeAvailable() const; // returns how much time is available for movement

	void markToTerminate(); // marks ball to be destroyed
	bool isMarkedAsTerminated() const; // should be destroyed?

	// returns the earliest collider which the ball will enter, can return nullptr if there is none
	Collider* bestFitCollider(const vector<Collider*>& colliders);

protected:
	float vx;
	float vy;

	float time_available = 0.0f; // time available for movement
	bool terminate = false; // is marked to be destroyed
};

