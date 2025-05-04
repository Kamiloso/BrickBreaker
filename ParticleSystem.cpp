#include "ParticleSystem.h"
#include "GameWindow.h"
#include "Scene.h"
#include "Input.h"
#include "Sound.h"

#include <cmath>
#include <stdexcept>

ParticleSystem::ParticleSystem(
	float _x,
	float _y,
	float _spread_radius,
	sf::Color _color,
	float _radius_min,
	float _radius_max,
	float _particle_count,
	float _emission_time,
	float _particle_minimum_lifetime,
	float _particle_maximum_lifetime,
	float _velocity_min,
	float _velocity_max,
	string sound_id,
	Scene* _scene,
	int _layer
) :
	SceneObject(_x, _y, _layer),
	spread_radius(_spread_radius),
	color(_color),
	radius_min(_radius_min),
	radius_max(_radius_max),
	particle_count(_particle_count),
	emission_time(_emission_time),
	particle_minimum_lifetime(_particle_minimum_lifetime),
	particle_maximum_lifetime(_particle_maximum_lifetime),
	velocity_min(_velocity_min),
	velocity_max(_velocity_max),
	scene(_scene),
	ms_twister(new mt19937(GameWindow::getEntropy()))
{
	// play sound
	if(sound_id != "")
		Sound::playSound(sound_id);
}

ParticleSystem::~ParticleSystem()
{
	delete ms_twister;
}

void ParticleSystem::setRectangularSpawn(float _rect_wx, float _rect_wy)
{
	rectangular_spawn = true;
	rect_wx = _rect_wx;
	rect_wy = _rect_wy;
}

void ParticleSystem::lateUpdate(float delta_time)
{
	total_life_time += delta_time;

	uniform_real_distribution<float> coords(-spread_radius, spread_radius);
	uniform_real_distribution<float> rect_coords_x(-rect_wx / 2, rect_wx / 2);
	uniform_real_distribution<float> rect_coords_y(-rect_wy / 2, rect_wy / 2);
	uniform_real_distribution<float> lifetime_multiplier(0, 1);
	uniform_real_distribution<float> angle_rand(0, 2 * PI);
	uniform_real_distribution<float> magnitude_rand(velocity_min, velocity_max);
	uniform_real_distribution<float> radius_rand(radius_min, radius_max);

	for (auto& particle : particles) {
		particle.frameUpdate(delta_time);
	}

	for (auto it = particles.begin(); it != particles.end();) {
		if (it->remainingLifetime() <= 0) {
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}

	if (total_number_of_particles > 1 && particles.empty()) {
		scene->markToDelete(this);
	}

	float how_much_to_do = total_life_time / emission_time;
	if (how_much_to_do > 1.0f)
		how_much_to_do = 1.0f;

	while (total_number_of_particles < (int)floor(how_much_to_do * particle_count)) {
		float particle_x{}, particle_y{};
		float lifetime = lifetime_multiplier(*ms_twister) * particle_maximum_lifetime + particle_minimum_lifetime;

		if (!rectangular_spawn) // circle
		{
			do {
				particle_x = coords(*ms_twister);
				particle_y = coords(*ms_twister);
			} while (pow(particle_x, 2) + pow(particle_y, 2) > pow(spread_radius, 2));
		}
		else // rectangle
		{
			particle_x = rect_coords_x(*ms_twister);
			particle_y = rect_coords_y(*ms_twister);
		}

		float particle_angle{}, particle_magnitude{}, p_vx, p_vy;
		particle_angle = angle_rand(*ms_twister);
		particle_magnitude = magnitude_rand(*ms_twister);
		p_vx = particle_magnitude * cos(particle_angle);
		p_vy = particle_magnitude * sin(particle_angle);

		particles.push_back(Particle(x - particle_x, y - particle_y, radius_rand(*ms_twister), p_vx, p_vy, lifetime));
		total_number_of_particles++;
	}
}

void ParticleSystem::draw(GameWindow* game_window)
{
	for (auto& particle : particles) {
		game_window->drawCircle(particle.getX(), particle.getY(),  particle.getRadius(), color);
	}
}


