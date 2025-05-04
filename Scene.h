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
	void markToDelete(SceneObject* old_ptr); // marks object with a given pointer to deletion in the next frame

	template<typename T>
	vector<T*> getObjectsOfType(); // returns a vector with every object of a given type

protected:
	SceneObject* addObject(SceneObject* new_ptr); // adds object (use "new" operand), should be PROTECTED
	virtual void sceneUpdate(float delta_time) = 0; // overridable scene update
	vector<SceneObject*> object_list;

private:
	bool deleteObjectByPointer(SceneObject* old_ptr); // deletes object with a given pointer if present on scene (returns success)
	vector<SceneObject*> objects_to_delete;
};

template<typename T>
inline vector<T*> Scene::getObjectsOfType()
{
	static_assert(std::is_base_of<SceneObject, T>::value, "T must derive from SceneObject");

	vector<T*> found_objects;
	for (SceneObject* object : object_list)
	{
		T* found_obj = dynamic_cast<T*>(object);
		if (found_obj != nullptr)
			found_objects.push_back(found_obj);
	}
	return found_objects;
}
