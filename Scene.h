#pragma once
#include <vector>
#include <map>

#include "common.h"

class SceneObject;
class GameWindow;

using namespace std;

// ------------------------------------------------------------------||
// The base object for every scene, this is a brain, take care of it ||
// ------------------------------------------------------------------||

class Scene
{
public:
	virtual ~Scene();
	vector<int> getEvents(); // returns a list of stored events
	void update(float delta_time); // updates all objects
	void drawScene(GameWindow* game_window); // draws all objects on screen
	SceneObject* addObject(SceneObject* new_ptr); // adds object (use "new" operand), returns itself (don't delete it)
	void markToDelete(SceneObject* old_ptr); // marks object with a given pointer to deletion in the next frame

protected:
	virtual void sceneUpdate(float delta_time) = 0; // overridable scene update
	vector<SceneObject*> object_list;

private:
	bool deleteObjectByPointer(SceneObject* old_ptr); // deletes object with a given pointer if present on scene (returns success)
	vector<SceneObject*> objects_to_delete;
};
