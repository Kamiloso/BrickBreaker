#include "EffectBounce.h"
#include "Scene.h"
#include "GameWindow.h"

#include <cmath>

EffectBounce::EffectBounce(float _x, float _y, Scene* _scene_ptr, int _layer)
	: SceneObject(_x, _y, _layer), scene_ptr(_scene_ptr),
	lasting_time(0.24f), radius(18.0f), base_color(sf::Color(25, 255, 25))
{
	if (!ENABLE_EXPERIMENTAL_BOUNCE_EFFECT)
		scene_ptr->markToDelete(this);
}

void EffectBounce::lateUpdate(float delta_time)
{
	if (time_elapsed >= lasting_time)
		scene_ptr->markToDelete(this);
	else
		time_elapsed += delta_time;
}

void EffectBounce::draw(GameWindow* game_window)
{
	float fraction = time_elapsed / lasting_time;
	game_window->drawCircle(x, y, radius * sizeByFraction(fraction), colorByFraction(base_color, fraction));
}

float EffectBounce::sizeByFraction(float fraction)
{
	if (fraction < 0.0f) fraction = 0.0f;
	if (fraction > 1.0f) fraction = 1.0f;
	return pow(fraction, 0.5f);
}

sf::Color EffectBounce::colorByFraction(sf::Color color, float fraction)
{
	if (fraction < 0.0f) fraction = 0.0f;
	if (fraction > 1.0f) fraction = 1.0f;
	color.a = (int)floor(255 * (0.9f - 0.9f * pow(fraction, 1.5f)));
	return color;
}
