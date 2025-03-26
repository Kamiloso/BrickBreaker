#include "Scene.h"
#include "SceneObject.h"

Scene::~Scene()
{
	// Destory all objects on a scene
	for (SceneObject* object : object_list)
		delete object;
	object_list.clear();
}

void Scene::update(float delta_time)
{
	sceneUpdate(delta_time);

	for (SceneObject* object : object_list)
		object->update(delta_time);

	for (SceneObject* object : objects_to_delete)
		deleteObjectByPointer(object);
	objects_to_delete.clear();
}

vector<int> Scene::getEvents()
{
	vector<int> return_vector = {};

	for (SceneObject* object : object_list)
	{
		int event_id = object->getEvent();
		if (event_id != 0)
			return_vector.push_back(event_id);
	}

	return return_vector;
}

SceneObject* Scene::addObject(SceneObject* new_ptr)
{
	object_list.push_back(new_ptr);
	return new_ptr;
}

void Scene::markToDelete(SceneObject* old_ptr)
{
	objects_to_delete.push_back(old_ptr);
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
