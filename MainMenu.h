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
	MainMenu(int localScene = 0); // Param used for changing local scene: param=0 for main menu, param=1 for levels menu, param=2 for instruction
	void sceneUpdate(float delta_time) override;
private:
	Rectangle* background;
	Text* title;
	Text* subtitle;
	Button* levels;
	Button* endless_btn;
	Button* instruction_btn;
	Button* exit_btn;
	vector<SceneObject*> menu_object_list;
	void changeLocalScene(int i); // moves everything by i * 10000 pixels forward (backwards if negative)
};
