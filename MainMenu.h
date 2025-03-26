#pragma once

#include "Scene.h"

using namespace std;

class MainMenu : public Scene
{
public:
	MainMenu();
	void sceneUpdate(float delta_time) override;
};
