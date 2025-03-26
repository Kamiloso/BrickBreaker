#include "GameScene.h"
#include "SceneObject.h"

GameScene::GameScene()
{
	addObject(new TempCircle(RX / 2, RY / 2, 500, sf::Color::Green));
}
