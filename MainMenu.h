#pragma once

#include "Scene.h"

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
	Text* title;
	Button* button1;
	Button* button2;
	Button* button3;
};
