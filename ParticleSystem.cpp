#include "ParticleSystem.h"
#include "GameWindow.h"
#include "cmath"
#include <stdexcept>
#include "iostream"

ParticleSystem::ParticleSystem(
	float _x,
	float _y,
	float _spread_radius,
	sf::Color _color,
	float _particle_count,
	float _particle_emission_gap,
	float _particle_minimum_lifetime,
	float _particle_maximum_lifetime,
	string sound_id,
	Scene* _scene,
	int _layer
) : 
SceneObject(_x, _y, _layer),
spread_radius(_spread_radius),
color(_color),
particle_count(_particle_count),
particle_emission_gap(_particle_emission_gap),
particle_minimum_lifetime(_particle_minimum_lifetime),
particle_maximum_lifetime(_particle_maximum_lifetime),
scene(_scene)
{
	ms_twister = new mt19937(GameWindow::getEntropy());
	if (_particle_minimum_lifetime <= 0) {
		throw runtime_error("Minimum lifetime must be greater than 0");
	}
	if (_particle_maximum_lifetime <= _particle_minimum_lifetime) {
		throw runtime_error("Maximum lifetime must be greater than minimum lifetime");
	}
}

ParticleSystem::~ParticleSystem()
{
	delete ms_twister;
}

void ParticleSystem::lateUpdate(float delta_time)
{
	total_life_time += delta_time;

	float  total_created_after_lu = total_life_time / (particle_emission_gap) + 1;

	int to_be_emmited = static_cast<int>(floor(total_created_after_lu)) - total_number_of_particles;

	uniform_real_distribution<float> coords(-spread_radius, spread_radius);
	uniform_real_distribution<float> lifetime_multiplier(0, 1);

	for (auto& particle : particles) {
		particle.reduceLifetimeBy(delta_time);
		particle.reduceRadius();
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

	if (total_number_of_particles >= particle_count) return;

	while (to_be_emmited > 0) {
		float particle_x{}, particle_y{};
		float lifetime = lifetime_multiplier(*ms_twister) * particle_maximum_lifetime + particle_minimum_lifetime;

		do {
			particle_x = coords(*ms_twister);
			particle_y = coords(*ms_twister);
		} while (pow(particle_x, 2) + pow(particle_y, 2) > pow(spread_radius, 2));

		particles.push_back(Particle(CX - particle_x, CY - particle_y, 5, 2, 2, lifetime));
		to_be_emmited--;
	}
	total_number_of_particles = total_created_after_lu;
}

void ParticleSystem::draw(GameWindow* game_window)
{
	for (auto& particle : particles) {
		game_window->drawCircle(particle.getX(), particle.getY(),  particle.getRadius(), color);
	}
}


