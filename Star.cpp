#include "Star.h"
#include "GameWindow.h"
#include "cmath"

Star::Star(float _x, float _y, float _r, mt19937* _gen, int _layer) : SceneObject(_x, _y, _layer), r(_r), gen(_gen) {
	uniform_real_distribution<> distFirstOpacityPhase(0, 255);
	opacity_time = distFirstOpacityPhase(*gen);
	uniform_real_distribution<> distPhase(0.3, 0.4);
	phase = distPhase(*gen);
}

void Star::draw(GameWindow* game_window) {
	game_window->drawCircle(x, y, r, color);
}

void Star::lateUpdate(float delta_time)
{
	opacity_time += delta_time;
	float opacity = (255.0 / 2.0) * (sin(phase * (opacity_time)) + 1);
	color = sf::Color(255, 255, 153, opacity);
}
