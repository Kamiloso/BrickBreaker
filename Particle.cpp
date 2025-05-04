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

void Particle::frameUpdate(float delta_time)
{
	// lifetime change
	lifetime -= delta_time;

	// position change
	x += vx * delta_time;
	y += vy * delta_time;

	// radius change
	//radius = starting_radius * (lifetime / total_lifetime);
	float fun_arg = 1.0f - lifetime / total_lifetime;
	if (fun_arg >= 0.0f && fun_arg <= 1.0f)
	{
		radius = starting_radius * sqrt(1 - fun_arg * fun_arg);
	}
	else
	{
		radius = 0.0f;
	}
}
