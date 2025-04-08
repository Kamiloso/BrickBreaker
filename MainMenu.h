#pragma once

#include "Scene.h"

class Rectangle;
class Star;
class Button;
class Text;

using namespace std;

// --------------------------------||
// Starting scene called main menu ||
// --------------------------------||

class MainMenu final : public Scene
{
public:
	MainMenu();
	void sceneUpdate(float delta_time) override;

private:
	Rectangle* background;
	Button* levels;
	Button* endless_btn;
	Button* instruction_btn;
	Button* exit_btn;
};
