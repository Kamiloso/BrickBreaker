#include "Particle.h"
#include <cmath>

Particle::Particle(float _x, float _y, float _radius, float _vx, float _vy, float _lifetime) : 
x(_x),
y(_y),
radius(_radius),
starting_radius(_radius),
vx(_vx),
vy(_vy),
lifetime(_lifetime),
total_lifetime(_lifetime)
{}

void Particle::reduceLifetimeBy(float delta_time) {
	lifetime -= delta_time;
}

void Particle::reduceRadius() {
	float time_elapsed = total_lifetime - lifetime;
	radius = (1 / total_lifetime) * lifetime * starting_radius;
}