#pragma once
#include "Rectangle.h"
#include "common.h"

class Collider;
class Scene;
class ParticleSystem;

constexpr float BRICK_SMALLER_BY = 4.0f; // width of the gap between bricks

class Brick : public Rectangle
{
public:
	enum ActionType {
		SpawnBalls, ReverseControl, SpeedUp, SlowDown, WiderPlate, ShorterPlate // etc.
	};

	Brick(float _x, float _y, int _health = 4, int _layer = 10);
	void damage(int dmg = 1); // damages the brick
	bool shouldBreak() const; // should scene break this brick in the following sceneUpdate?
	bool touchesRect(const Rectangle* rect) const; // checks if brick touches a given rect (uses BRICK_SMALLER_BY to be more precise)
	vector<Collider*> createNewColliders(bool up, bool down, bool left, bool right); // creates brick colliders on heap and returns vector of them

	// Override these methods
	virtual bool unbreakable() { return false; } // can't be broken and is not needed to win
	virtual bool goesThrough() { return false; } // doesn't bounce the ball on destroy
	virtual vector<ActionType> getActionsOnBounce() { return {  }; } // returns actions which should be executed on bounce
	virtual vector<ActionType> getActionsOnDestroy() { return {  }; } // returns actions which should be executed on destroy
	virtual ParticleSystem* createNewBreakParticles(Scene* scene); // creates destroy particle system
	void draw(GameWindow* game_window) override; // draws the brick, override this once again

	static vector<float> getBrickPositionByCoordinates(int x, int y); // returns brick positions based on slot coordinates

protected:
	int health;
};
