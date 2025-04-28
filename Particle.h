#pragma once
class Particle
{
private:
	float x; // starting x position
	float y; // starting y position
	float radius;
	float vx; // velocity on x
	float vy; // velocity on y
	float life_time;
public:
	Particle(float _x, float _y, float _radius, float _vx, float _vy, float _life_time);
	float remainingLifeTime();
	void moveByDeltaTime();
	float getX() { return x; }
	float getY() { return y; }
	float getRadius() { return radius; }
};

