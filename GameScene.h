#pragma once

#include "Scene.h"
#include "Rectangle.h"
#include "Ball.h"
#include "Collider.h"
#include "Grid.h"

class SceneObject;
class Button;
class Text;

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
	void populateGrid(Grid* grid);

private:
	const int ROWS = 15;
	const int COLS = 10;
	float left_margin = 300;
	float right_margin = -left_margin;
	
	Rectangle* left_wall;
	Rectangle* right_wall;
	Ball* ball1;
	Collider* collider1;
	Grid* grid1;

	//-----
	const int level; // level ID
	int local_screen = 0; // 1 = pause, 2 = win screen, 3 = defeat screen (screens are at local_screen * 10000 coordinates)
	int local_screen_before = 0; // last frame local_screen ID
	vector<SceneObject*> pause_menu_objects = {}; // put here all local screen objects

	Text* level_num_text;

	bool was_escape_pressed = true; // was escape pressed in the frame before?
};
