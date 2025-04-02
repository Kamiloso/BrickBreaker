#pragma once
#include <string>

#include "Rectangle.h"

class Text;

using namespace std;

// -------------------------------------------||
// Button class for detecting player UI input ||
// -------------------------------------------||

enum ButtonState {
	Default, Highlighted,
	Pressed, Disabled
};

class Button : public Rectangle
{
public:
	Button(float _x, float _y, float _wx, float _wy, sf::Color _button_color, const wstring& _text, int _layer = 20);
	~Button();
	void setEvent(int _event_id, bool _to_window); // specifies button event and how publish it after clicking
	void earlyUpdate(float delta_time) override;
	void draw(GameWindow* game_window) override;
	int getEventToScene() override;
	int getEvent() override;
	void setPosition(float _x, float _y) override;

	static sf::Color getButtonColor(const sf::Color& base_color, ButtonState state); // returns button color

protected:
	Text* internal_text; // internal text scene object (access and management only from this class)
	GameWindow* game_window_ptr = nullptr; // game window for access when needed

	// Class variables
	ButtonState button_state = Disabled; // which color to set? (only affects visuals)
	bool to_window = false; // send event to window class?
	int event_id = 0; // which event to send?
	bool was_pressed = false; // was recently pressed?
	bool is_holding = false; // is button selected and catched?
	bool is_clicked = true; // is mouse clicked? (was in the previous frame)

private:
	int getRawEvent();
};
