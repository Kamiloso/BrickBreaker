#include "Brick.h"
#include "GameWindow.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "Ball.h"
#include "ParticleSystem.h"
#include "Scene.h"

Brick::Brick(float _x, float _y, int _health, int _layer) : health(_health),
	Rectangle(_x, _y, BRICK_WX, BRICK_WY, 3, COL::brick, sf::Color::Black, _layer) {}

void Brick::damage(int dmg)
{
	health -= dmg;
}

bool Brick::shouldBreak() const
{
	return health <= 0;
}

bool Brick::touchesRect(const Rectangle* rect) const
{
	auto rect_pos = rect->getPosition();
	auto rect_sca = rect->getScale();

	float cent_diff_x = abs(rect_pos[0] - x);
	float cent_diff_y = abs(rect_pos[1] - y);

	float filled_x = (rect_sca[0] + wx - BRICK_SMALLER_BY) / 2;
	float filled_y = (rect_sca[1] + wy - BRICK_SMALLER_BY) / 2;

	return (filled_x > cent_diff_x && filled_y > cent_diff_y);
}

vector<Collider*> Brick::createNewColliders(bool up, bool down, bool left, bool right)
{
	vector<Collider*> new_colliders = {};
	new_colliders.reserve(8);

	// calculate vertices coordinates
	float vx1 = x - wx / 2 + (left * BRICK_SMALLER_BY / 2);
	float vx2 = x + wx / 2 - (right * BRICK_SMALLER_BY / 2);
	float vy1 = y - wy / 2 + (up * BRICK_SMALLER_BY / 2);
	float vy2 = y + wy / 2 - (down * BRICK_SMALLER_BY / 2);

	// create line colliders
	if (up) new_colliders.push_back(
		new LineCollider(vx1, vy1 - BALL_RADIUS, vx2, vy1 - BALL_RADIUS, LineCollider::Up, this)
	);
	if (down) new_colliders.push_back(
		new LineCollider(vx1, vy2 + BALL_RADIUS, vx2, vy2 + BALL_RADIUS, LineCollider::Down, this)
	);
	if (left) new_colliders.push_back(
		new LineCollider(vx1 - BALL_RADIUS, vy1, vx1 - BALL_RADIUS, vy2, LineCollider::Left, this)
	);
	if (right) new_colliders.push_back(
		new LineCollider(vx2 + BALL_RADIUS, vy1, vx2 + BALL_RADIUS, vy2, LineCollider::Right, this)
	);

	// create corner (sphere) colliders
	if (left && up) new_colliders.push_back(
		new CircleCollider(vx1, vy1, BALL_RADIUS, this)
	);
	if (up && right) new_colliders.push_back(
		new CircleCollider(vx2, vy1, BALL_RADIUS, this)
	);
	if (right && down) new_colliders.push_back(
		new CircleCollider(vx2, vy2, BALL_RADIUS, this)
	);
	if (down && left) new_colliders.push_back(
		new CircleCollider(vx1, vy2, BALL_RADIUS, this)
	);

	return new_colliders;
}

ParticleSystem* Brick::createNewBreakParticles(Scene* scene)
{
	auto ret = new ParticleSystem(
		x, y, 1.0f, color,
		4.0f, 6.0f,		/* SIZE */
		9,				/* COUNT */
		0.01f,			/* EMISSION TIME */
		0.12f, 0.2f,	/* LIFETIME */
		60.0f, 80.0f,	/* SPEED */
		0.35f,			/* BOLD */
		break_sound,	/* SOUND */
		scene, 15		/* LAYER */
	);
	ret->setRectangularSpawn(wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY);
	return ret;
}

void Brick::draw(GameWindow* game_window)
{
	// Similar to drawing rectangle, but smaller (will change in the future)
	game_window->drawRectangle(x, y, wx - BRICK_SMALLER_BY, wy - BRICK_SMALLER_BY, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2 - BRICK_SMALLER_BY, wy - bold * 2 - BRICK_SMALLER_BY, color);
}

vector<float> Brick::getBrickPositionByCoordinates(int x, int y)
{
	const float COLUMN_0_X = CX - (BRICKS_X - 1) * BRICK_WX / 2;
	const float LAYER_0_Y = 50.0f;
	return {
		COLUMN_0_X + x * BRICK_WX,
		LAYER_0_Y + y * BRICK_WY
	};
}
