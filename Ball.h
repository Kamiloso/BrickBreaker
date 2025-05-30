#pragma once
#include "Circle.h"
#include <vector>

class Collider;
class ParticleSystem;
class Scene;

static constexpr float BALL_RADIUS = 12.0f; // constant ball radius source

class Ball : public Circle
{
public:
	Ball(float _x, float _y, int _layer = 12);
	void step(float time);

	void setVelocity(float _vx, float _vy);
	void setVelocityByAngle(float angle, float magnitude); // degrees
	vector<float> getVelocity() const;
	float getVelocityAngle() const;
	float getVelocityMagnitude() const;

	void changeSpeedPowerUps(int delta_speed_modifier); // changes velocity using power up

	void resetTime(); // resets available time for movement
	void changeTime(float time); // changes available time for movement
	float getTimeAvailable() const; // returns how much time is available for movement

	// create destroy particles
	ParticleSystem* createNewDestroyParticles(Scene* scene);

	// returns the earliest collider which the ball will enter, can return nullptr if there is none
	Collider* bestFitCollider(const vector<Collider*>& colliders);

	void setBouncedFlag(bool flag); // sets frame_bounced flag to given value
	bool getBouncedFlag() const; // returns frame_bounced flag

	// THIS CLASS CAN BE COPIED
	Ball(const Ball&) = default;
	Ball& operator=(const Ball&) = default;

protected:
	float vx;
	float vy;

	float time_available = 0.0f; // time available for movement
	bool frame_bounced = false; // was bounced in this frame?

	int speed_modifier = 0; // current modifier from power-ups
};
