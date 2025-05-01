#pragma once
#include "Brick.h"

class Plate;

class SizeBrick : public Brick
{
public:
	SizeBrick(float _x, float _y, bool _mode, const Plate* _plate = nullptr, int _layer = 10);
	vector<ActionType> getActionsOnDestroy() override;
	void draw(GameWindow* game_window) override;

private:
	sf::Texture* texture = nullptr;
	sf::Texture* texture2 = nullptr; // when reversed
	bool mode;
	const Plate* plate;
};
