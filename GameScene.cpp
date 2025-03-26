#include "GameScene.h"
#include "SceneObject.h"

GameScene::GameScene()
{
	temp_big_circle = addObject(new TempCircle(RX / 2, RY / 2, 500, sf::Color::Green));
}

void GameScene::sceneUpdate(float delta_time)
{
	if (temp_big_circle != nullptr && temp_big_circle->getEventToScene() == 1)
	{
		markToDelete(temp_big_circle);
		temp_big_circle = nullptr;
		addObject(new TempCircle(RX / 2, RY / 2 + 300, 50, sf::Color::Green));
		addObject(new TempCircle(RX / 2, RY / 2 - 300, 50, sf::Color::Green));
	}
	for (SceneObject* object : object_list)
	{
		sf::Vector2<float> pos = object->getPosition();
		object->setPosition(sf::Vector2<float>(pos.x, pos.y + 20 * delta_time));
	}
}
