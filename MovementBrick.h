#pragma once
#include "Brick.h"

class MovementBrick : public Brick
{
public:
	MovementBrick(float _x, float _y, bool _mode, int _layer = 10);
	bool unbreakable() override { return true; }
	vector<ActionType> getActionsOnBounce() override;
	void draw(GameWindow* game_window) override;

	void specialMovementUpdate(float delta_time); // executes once per frame from sceneUpdate
	void activateVisual(); // activates second texture for some time

private:
	sf::Texture* texture = nullptr;
	sf::Texture* texture2 = nullptr; // when active
	bool mode;
	float visual_counter = 0.0f;
};

