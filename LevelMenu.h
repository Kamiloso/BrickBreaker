#pragma once

#include "Scene.h"

using namespace std;

// ---------------------||
// Level selection menu ||
// ---------------------||

class LevelMenu : public Scene
{
public:
	LevelMenu();
	void sceneUpdate(float delta_time) override;
};
