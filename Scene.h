#pragma once
#include <vector>

class SceneObject;
class GameWindow;

using namespace std;

class Scene
{
public:
	~Scene();
	void addObject(SceneObject* new_ptr); // adds object (use "new" operand)
	bool deleteObjectByPointer(SceneObject* old_ptr); // deletes object with a given pointer if present on scene (returns success)
	void drawScene(GameWindow* game_window); // draws all objects on screen

private:
	vector<SceneObject*> object_list;
};
