#pragma once
#include "SceneObject.h"
#include "Particle.h"
#include "Scene.h"
#include <vector>
#include <random>
using namespace std;

class GameWindow;

class ParticleSystem : public SceneObject
{
private:
	float spread_radius;
	sf::Color color;
	float particle_count; // amount of particles to be emissioned
	float particle_emission_gap; // time between emissions
	vector<Particle> particles;
	float total_life_time = 0;
	int total_number_of_particles = 0; // number of created particles
	mt19937* ms_twister;
	float particle_minimum_lifetime;
	float particle_maximum_lifetime;
	Scene* scene;
public:
	ParticleSystem(
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
	);
	~ParticleSystem();
	void lateUpdate(float delta_time) override;
	void draw(GameWindow* game_window) override;
};

