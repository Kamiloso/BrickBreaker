#include "Button.h"
#include "GameWindow.h"
#include "Text.h"

Button::Button(float _x, float _y, float _wx, float _wy, sf::Color _button_color, const wstring& _text, int _layer)
	: Rectangle(_x, _y, _wx, _wy, 10.0f, _button_color, sf::Color::Black, _layer)
{
	// Create internal text
	internal_text = new Text(x, y, _text, 0.6f * (wy - 20.0f), color_bold);

	// Set button colors
	color_default = _button_color;
	color_highlighted = sf::Color::Cyan;
	color_pressed = sf::Color::Yellow;
	color_disabled = sf::Color::Black;
}

Button::~Button()
{
	delete internal_text;
}

void Button::setEvent(int _event_id, bool _to_window)
{
	event_id = _event_id;
	to_window = _to_window;
}

void Button::lateUpdate(float delta_time)
{
	// Change button colors right before scene drawing
	switch (button_state)
	{
	case Default: color = color_default; break;
	case Highlighted: color = color_highlighted; break;
	case Pressed: color = color_pressed; break;
	case Disabled: color = color_disabled; break;
	}
}

void Button::draw(GameWindow* game_window)
{
	game_window->drawRectangle(x, y, wx, wy, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2, wy - bold * 2, color);
	internal_text->draw(game_window);
}

int Button::getEventToScene()
{
	if (to_window) return 0; // if not this event type, return 0
	return getRawEvent();
}

int Button::getEvent()
{
	if (!to_window) return 0; // if not this event type, return 0
	return getRawEvent();
}

int Button::getRawEvent()
{
	if (was_pressed)
	{
		was_pressed = false;
		return event_id;
	}
	else return 0;
}
