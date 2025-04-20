#pragma once
#include "Scene.h"

class SceneObject;
class Rectangle;
class Button;
class Text;
class Brick;
class Plate;
class Ball;
class Collider;

using namespace std;

// --------------------||
// The main game scene ||
// --------------------||

class GameScene final : public Scene
{
public:
	GameScene(int _level);
	~GameScene();
	void sceneUpdate(float delta_time) override;

	static const float border_left; // right border coords
	static const float border_right; // left border coords
	static const float zone_down; // zone under which balls are destroyed

private:
	float border_up; // upper border coords

	const int level; // level ID
	int brick_fall_time = 0; // settings loaded from level data (choose default endless value)
	float ball_max_speed = 0.0f; // settings loaded from level data (choose default endless value)

	int local_screen = 0; // 1 = pause, 2 = win screen, 3 = defeat screen (screens are at local_screen * 10000 coordinates)
	int local_screen_before = 0; // last frame local_screen ID
	float fall_time_counter = 0.0f; // time elapsed from last brick fall
	int brick_falls_done = 0; // brick falls that have been done already

	vector<SceneObject*> pause_menu_objects = {}; // put here all local screen objects
	Text* level_num_text; // that "01 / 40" thing in the corner

	// fixed array of all bricks
	Brick* bricks[BRICKS_X][BRICKS_Y]{};

	Rectangle* crusher; // upper wall, that moves down and you can not do anything about that
	Plate* plate; // one single movable plate that bounces the ball
	vector<Ball*> balls; // contains all balls present on a scene

	vector<Collider*> colliders; // vector of all colliders (changes dynamically on brick update)
	void updateColliders(); // updates colliders to fit current brick array

	void initializeGame(); // initializes static visible scene objects
	void initializeUI(); // initializes UI
	void populateGrid(int level_id); // initializes bricks from a given level_id

	bool canMoveDownEverything(bool with_crusher); // checks if can move the level down
	void moveDownEverything(bool with_crusher); // moves down all bricks (and the crusher)

	void applyGravity(float g); // applies gravitational force to all balls (experimental)
	void handlePhysics(float delta_time); // ball movement, brick breaking etc.
};
