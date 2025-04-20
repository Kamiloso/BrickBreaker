#include "Collider.h"

Collider::Collider(Brick* _brick) : brick(_brick) {}

Brick* Collider::getBrick()
{
	return brick;
}
