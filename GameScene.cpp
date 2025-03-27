#include "GameScene.h"
#include "SceneObject.h"

GameScene::GameScene()
{
	temp_big_circle = addObject(new TempCircle(RX / 2, RY / 2, 500, sf::Color::Green));
}

void GameScene::sceneUpdate(float delta_time)
{
	if (temp_big_circle != nullptr)
	{
		if (temp_big_circle->getEventToScene() == 1)
		{
			markToDelete(temp_big_circle);
			temp_big_circle = nullptr; // make sure to reset after deletion (here it is not needed)
			temp_big_circle = addObject(new TempCircle(RX / 2, RY / 2 + 300, 50, sf::Color::Green));
			addObject(new TempCircle(RX / 2, RY / 2 - 300, 50, sf::Color::Green));
		}

		TempCircle* temp_circle = dynamic_cast<TempCircle*>(temp_big_circle);
		if (temp_circle != nullptr)
			temp_circle->step(delta_time);
	}
}
