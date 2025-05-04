#include "Button.h"
#include "GameWindow.h"
#include "Text.h"
#include "Input.h"

Button::Button(float _x, float _y, float _wx, float _wy, sf::Color _button_color, sf::Color _bold_color, const wstring& _text, int _layer)
	: Rectangle(_x, _y, _wx, _wy, 10.0f, _button_color, _bold_color, _layer)
{
	// Create internal text
	internal_text = new Text(x, y, _text, (int)(0.6f * (wy - 20.0f)), color_bold);
}

Button::~Button()
{
	delete internal_text;
}

void Button::setEvent(int _event_id, bool _to_window)
{
	event_id = _event_id;
	to_window = _to_window;

	if (event_id == 0)
		button_state = Disabled;
	else
		button_state = Default;
}

void Button::visualAdvanced(float _bold)
{
	bold = _bold;
}

void Button::earlyUpdate(float delta_time)
{
	// Button click logic
	if (event_id != 0)
	{
		auto mvect = Input::getMousePosition();
		sf::Vector2f mouse_pos = {
			mvect[0],
			mvect[1]
		};

		bool is_in_area_now = (
			mouse_pos.x >= x - wx / 2 && mouse_pos.x <= x + wx / 2 &&
			mouse_pos.y >= y - wy / 2 && mouse_pos.y <= y + wy / 2
			);
		bool is_clicked_now = Input::isMousePressed(sf::Mouse::Left);

		if (is_holding)
		{
			if (is_clicked_now)
			{
				button_state = Pressed;
			}
			else
			{
				if (is_in_area_now)
				{
					// Do not highlight, one frame delay sometimes needed
					was_pressed = true;
				}
				else
				{
					button_state = Default;
				}
				is_holding = false;
			}
		}
		else
		{
			if (is_in_area_now)
			{
				if (!is_clicked && is_clicked_now)
				{
					button_state = Pressed;
					is_holding = true;
				}
				else
				{
					if (is_clicked_now)
					{
						button_state = Default;
					}
					else
					{
						button_state = Highlighted;
					}
				}
			}
			else
			{
				button_state = Default;
			}
		}

		is_clicked = is_clicked_now;
	}
}

void Button::draw(GameWindow* game_window)
{
	game_window->drawRectangle(x, y, wx, wy, color_bold);
	game_window->drawRectangle(x, y, wx - bold * 2, wy - bold * 2, getButtonColor(color, button_state));
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

void Button::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
	internal_text->setPosition(x, y);
}

sf::Color Button::getButtonColor(const sf::Color& base_color, ButtonState state)
{
	switch (state) {
	case ButtonState::Default:
		return base_color;

	case ButtonState::Highlighted:
		return sf::Color(
			static_cast<sf::Uint8>(base_color.r * 0.86f),
			static_cast<sf::Uint8>(base_color.g * 0.86f),
			static_cast<sf::Uint8>(base_color.b * 0.86f),
			base_color.a
		);

	case ButtonState::Pressed:
		return sf::Color(
			static_cast<sf::Uint8>(base_color.r * 0.72f),
			static_cast<sf::Uint8>(base_color.g * 0.72f),
			static_cast<sf::Uint8>(base_color.b * 0.72f),
			base_color.a
		);

	case ButtonState::Disabled:
		sf::Uint8 gray = static_cast<sf::Uint8>(
			(0.299f * base_color.r + 0.587f * base_color.g + 0.114f * base_color.b) * 0.85f
			);
		return sf::Color(gray, gray, gray, base_color.a);
	}
	return base_color;
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
