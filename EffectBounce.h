#pragma once
#include "SceneObject.h"

class Scene;

class EffectBounce final : public SceneObject
{
public:
	EffectBounce(float _x, float _y, Scene* _scene_ptr, int _layer = 9);
	void lateUpdate(float delta_time) override;
	void draw(GameWindow* game_window) override;

	static float sizeByFraction(float fraction);
	static sf::Color colorByFraction(sf::Color color, float fraction);

private:

	float time_elapsed = 0.0f;
	float lasting_time;
	float radius;
	sf::Color base_color;
	Scene* scene_ptr;
};
