#include "LevelMenu.h"
#include "Text.h"
#include "Button.h"

LevelMenu::LevelMenu()
{
	addObject(new Text(CCX, CCY - 60, L"This scene should never display!", 80));

	Button* back_and_forget = new Button(CCX, CCY + 60, 500, 100, sf::Color::White, sf::Color::Black, L"BACK AND FORGET");
	addObject(back_and_forget);
	back_and_forget->setEvent(1000, true);
}

void LevelMenu::sceneUpdate(float delta_time)
{
	// whis function should be empty
}
