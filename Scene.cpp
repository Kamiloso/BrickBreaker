#include "Scene.h"
#include "SceneObject.h"

Scene::~Scene()
{
	// Destory all objects on a scene
	for (SceneObject* object : object_list)
		delete object;
	object_list.clear();
}

void Scene::addObject(SceneObject* new_ptr)
{
	object_list.push_back(new_ptr);
}

bool Scene::deleteObjectByPointer(SceneObject* old_ptr)
{
	for (auto it = object_list.begin(); it != object_list.end(); ++it)
	{
		if (*it == old_ptr)
		{
			delete (*it);
			object_list.erase(it);
			return true; // erasing only one element
		}
	}
	return false;
}

void Scene::drawScene(GameWindow* game_window)
{
	for (SceneObject* object : object_list)
		object->draw(game_window);
}
