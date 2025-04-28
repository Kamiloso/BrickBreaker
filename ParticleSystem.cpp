#include "ParticleSystem.h"
#include "GameWindow.h"
#include "cmath"
#include "iostream"

ParticleSystem::ParticleSystem(
	float _x,
	float _y,
	float _spread_radius,
	sf::Color _color,
	float _particle_count,
	float _particle_emission_gap,
	string sound_id,
	int _layer
) : SceneObject(_x, _y, _layer),
spread_radius(_spread_radius),
color(_color),
particle_count(_particle_count),
particle_emission_gap(_particle_emission_gap) {

}

void ParticleSystem::lateUpdate(float delta_time)
{
	total_life_time += delta_time;
	//cout << " ...." << endl << total_number_of_particles << " " << particle_count << endl;
	if (total_number_of_particles >= particle_count) return;

	float  total_created_after_lu = total_life_time / (particle_emission_gap) + 1;

	int to_be_emmited = static_cast<int>(floor(total_created_after_lu)) - total_number_of_particles;
	cout << to_be_emmited << " " << total_number_of_particles << " " << total_created_after_lu << endl;
	while (to_be_emmited > 0) {
		particles.push_back(Particle(CX, CX, 30, 2, 2, 4));
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


