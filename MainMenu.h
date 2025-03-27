#pragma once

#include "Scene.h"

using namespace std;

// --------------------------------||
// Starting scene called main menu ||
// --------------------------------||

class MainMenu : public Scene
{
public:
	MainMenu();
	void sceneUpdate(float delta_time) override;
};
