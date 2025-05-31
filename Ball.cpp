#include "Ball.h"
#include "GameWindow.h"
#include "GameScene.h"
#include "Sound.h"
#include "Collider.h"
#include "ParticleSystem.h"

Ball::Ball(float _x, float _y, int _layer)
	: Circle(_x, _y, BALL_RADIUS, 3, COL::ball, sf::Color::Black, _layer),
	vx(0), vy(0) {}

void Ball::step(float time)
{
	x += vx * time;
	y += vy * time;
}

void Ball::setVelocity(float _vx, float _vy)
{
	vx = _vx;
	vy = _vy;
}

void Ball::setVelocityByAngle(float angle, float magnitude)
{
	setVelocity(
		cos(angle * PI / 180) * magnitude,
		sin(angle * PI / 180) * magnitude
	);
}

vector<float> Ball::getVelocity() const
{
	return { vx, vy };
}

float Ball::getVelocityAngle() const
{
	if (vx != 0.0f || vy != 0.0f)
		return atan2(vy, vx) * 180 / PI;
	else
		return 90.0f;
}

float Ball::getVelocityMagnitude() const
{
	return sqrt(vx * vx + vy * vy);
}

void Ball::changeSpeedPowerUps(int delta_speed_modifier)
{
	constexpr float SPEED_MODIFIER_FACTOR_NEGATIVE = 1.12f;
	constexpr float SPEED_MODIFIER_FACTOR_POSITIVE = 1.20f;
	constexpr int MIN_SPEED_MODIFIER = -3;
	constexpr int MAX_SPEED_MODIFIER = 3;

	int next_speed_modifier = speed_modifier + delta_speed_modifier;

	if (next_speed_modifier < MIN_SPEED_MODIFIER)
		next_speed_modifier = MIN_SPEED_MODIFIER;

	if (next_speed_modifier > MAX_SPEED_MODIFIER)
		next_speed_modifier = MAX_SPEED_MODIFIER;

	delta_speed_modifier = next_speed_modifier - speed_modifier;

	int down_speeds = 0, up_speeds = 0;
	int discrete_delta = delta_speed_modifier > 0 ? 1 : -1;

	while (speed_modifier != next_speed_modifier)
	{
		// negative side
		if (speed_modifier < 0 || (speed_modifier == 0 && discrete_delta == -1))
			down_speeds += discrete_delta;

		// positive side
		if (speed_modifier > 0 || (speed_modifier == 0 && discrete_delta == 1))
			up_speeds += discrete_delta;

		speed_modifier += discrete_delta;
	}

	setVelocityByAngle(
		getVelocityAngle(),
		getVelocityMagnitude() *
		pow(SPEED_MODIFIER_FACTOR_NEGATIVE, down_speeds) *
		pow(SPEED_MODIFIER_FACTOR_POSITIVE, up_speeds)
	);
}

void Ball::resetTime()
{
	time_available = 0.0f;
}

void Ball::changeTime(float time)
{
	time_available += time;
}

float Ball::getTimeAvailable() const
{
	return time_available;
}

ParticleSystem* Ball::createNewDestroyParticles(Scene* scene)
{
	return new ParticleSystem(
		x, y, 20.0f, color,
		6.0f, 8.0f,		/* SIZE */
		3,				/* COUNT */
		0.01f,			/* EMISSION TIME */
		0.2f, 0.25f,	/* LIFETIME */
		150.0f, 200.0f, /* SPEED */
		0.3f,			/* BOLD */
		"ball-break",	/* SOUND */
		scene, 15		/* LAYER */
	);
}

Collider* Ball::bestFitCollider(const vector<Collider*>& colliders)
{
	Collider* best_fit = nullptr;
	float best_time_to_collision = std::numeric_limits<float>::infinity();

	for (Collider* collider : colliders)
	{
		float time_to_collision = collider->getTimeToCollision(this);
		if (time_to_collision != NO_COLLISION && time_to_collision < best_time_to_collision)
		{
			best_fit = collider;
			best_time_to_collision = time_to_collision;
		}
	}

	return best_fit;
}

void Ball::setBouncedFlag(bool flag)
{
	frame_bounced = flag;
}

bool Ball::getBouncedFlag() const
{
	return frame_bounced;
}
