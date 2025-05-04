#pragma once
#include "SceneObject.h"
#include "Particle.h"

#include <vector>
#include <random>

using namespace std;

class GameWindow;
class Scene;

class ParticleSystem : public SceneObject
{
private:
	float spread_radius;
	sf::Color color;
	float particle_count; // amount of particles to be emissioned
	float emission_time; // total time, which will be emitting
	vector<Particle> particles;
	float total_life_time = 0;
	int total_number_of_particles = 0; // number of created particles
	mt19937* ms_twister;
	float radius_min;
	float radius_max;
	float particle_minimum_lifetime;
	float particle_maximum_lifetime;
	float velocity_min;
	float velocity_max;
	Scene* scene;
	bool rectangular_spawn = false;
	float rect_wx, rect_wy;
public:
	ParticleSystem(
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
	);
	~ParticleSystem();
	void setRectangularSpawn(float _rect_wx, float _rect_wy); // replaces default circle spawning with a rectangular spawning
	void lateUpdate(float delta_time) override;
	void draw(GameWindow* game_window) override;
};

