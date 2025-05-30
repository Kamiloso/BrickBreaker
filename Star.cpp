#include "Star.h"
#include "GameWindow.h"
#include "Rectangle.h"

#include <cmath>

Star::Star(float _x, float _y, float _r, mt19937* gen, int _layer) : SceneObject(_x, _y, _layer), r(_r) {
	uniform_real_distribution<> distFirstOpacityPhase(0, 255);
	opacity_time = distFirstOpacityPhase(*gen);
	uniform_real_distribution<> distPhase(0.8, 2);
	phase = distPhase(*gen);
}

void Star::draw(GameWindow* game_window) {
	game_window->drawCircle(x, y, r, color);
}

void Star::lateUpdate(float delta_time)
{
	opacity_time += delta_time;
	//float opacity = (255.0 / 2.0) * (sin(phase * (opacity_time)) + 1);
	float opacity = (255.0 / 2.0) * (-1.0 / 4.0 * pow(2.84, 2 * sin(opacity_time * phase)) + 2.017);
	color = sf::Color(255, 255, 153, opacity);
}

bool Star::centerInRect(Rectangle* rect)
{
	auto rect_pos = rect->getPosition();
	auto rect_sca = rect->getScale();
	return (
		(x >= rect_pos[0] - rect_sca[0] / 2 && x <= rect_pos[0] + rect_sca[0] / 2) &&
		(y >= rect_pos[1] - rect_sca[1] / 2 && y <= rect_pos[1] + rect_sca[1] / 2)
		);
}
