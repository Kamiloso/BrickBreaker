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
	void lateUpdate(float delta_time) override;
	void draw(GameWindow* game_window) override;
	int getEventToScene() override;
	int getEvent() override;

protected:
	Text* internal_text; // internal text scene object

	// Class variables
	ButtonState button_state = Default; // which color to set and how the button will behave
	bool to_window = false; // send event to window class?
	int event_id = 0; // which event to send?
	bool was_pressed = false; // was recently pressed?

	// Button colors, set in constructor
	sf::Color color_default;
	sf::Color color_highlighted;
	sf::Color color_pressed;
	sf::Color color_disabled;

private:
	int getRawEvent();
};
