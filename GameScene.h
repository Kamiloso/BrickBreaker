#pragma once

#include "Scene.h"

class SceneObject;

using namespace std;

// --------------------||
// The main game scene ||
// --------------------||

class GameScene : public Scene
{
public:
	GameScene();
	void sceneUpdate(float delta_time) override;

protected:
	SceneObject* temp_big_circle;
};
