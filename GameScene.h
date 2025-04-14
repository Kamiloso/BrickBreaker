#pragma once

#include "Scene.h"
#include "Rectangle.h"
#include "Ball.h"
#include "Collider.h"
#include "Grid.h"
#include "Sound.h"
#include <SFML/Audio.hpp>

class SceneObject;
class Button;

using namespace std;

// --------------------||
// The main game scene ||
// --------------------||

class GameScene : public Scene
{
public:
	GameScene();
	void sceneUpdate(float delta_time) override;
	void populateGrid(Grid* grid);
	
protected:
	const int ROWS = 15;
	const int COLS = 10;
	float left_margin = 300;
	float right_margin = -left_margin;
	Button* button1;
	Rectangle* left_wall;
	Rectangle* right_wall;
	Ball* ball1;
	Collider* collider1;
	Grid* grid1;
};
