#pragma once
class Particle
{
private:
	float x; // starting x position
	float y; // starting y position
	float radius;
	float starting_radius;
	float vx; // velocity on x
	float vy; // velocity on y
	float lifetime;
	float total_lifetime;
public:
	Particle(float _x, float _y, float _radius, float _vx, float _vy, float _lifetime);
	float remainingLifetime() const { return lifetime; };
	float getX() const { return x; }
	float getY() const { return y; }
	float getRadius() const { return radius; }
	void frameUpdate(float delta_time);
};

