#include "Input.h"
#include "GameWindow.h"

GameWindow* Input::game_window = nullptr;
float Input::mouse_x = -10000.0f;
float Input::mouse_y = -10000.0f;
unordered_set<sf::Keyboard::Key> Input::keyboard_hold;
unordered_set<sf::Keyboard::Key> Input::keyboard_down;
unordered_set<sf::Keyboard::Key> Input::keyboard_up;
unordered_set<sf::Mouse::Button> Input::mouse_hold;
unordered_set<sf::Mouse::Button> Input::mouse_down;
unordered_set<sf::Mouse::Button> Input::mouse_up;

void Input::init(GameWindow* _game_window)
{
	game_window = _game_window;
}

void Input::frameUpdate(float _mouse_x, float _mouse_y, unordered_set<sf::Keyboard::Key> _keyboard_clicked, unordered_set<sf::Mouse::Button> _mouse_clicked)
{
	// mouse position set
	mouse_x = _mouse_x;
	mouse_y = _mouse_y;

	// keyboard update
	auto k_hold = keyboard_hold; keyboard_hold.clear();
	keyboard_down.clear();
	keyboard_up.clear();

	auto k_all = k_hold;
	k_all.insert(_keyboard_clicked.begin(), _keyboard_clicked.end());

	for (const auto& key : k_all)
	{
		bool clicked = (_keyboard_clicked.find(key) != _keyboard_clicked.end());
		bool hold = (k_hold.find(key) != k_hold.end());

		if (clicked) // hold when clicked
			keyboard_hold.insert(key);

		if (clicked && !hold) // down when clicked and wasn't hold before
			keyboard_down.insert(key);

		if (!clicked && hold) // up when not clicked, but was hold
			keyboard_up.insert(key);
	}

	// mouse update
	auto m_hold = mouse_hold; mouse_hold.clear();
	mouse_down.clear();
	mouse_up.clear();

	auto m_all = m_hold;
	m_all.insert(_mouse_clicked.begin(), _mouse_clicked.end());

	for (const auto& mkey : m_all)
	{
		bool clicked = (_mouse_clicked.find(mkey) != _mouse_clicked.end());
		bool hold = (m_hold.find(mkey) != m_hold.end());

		if (clicked) // hold when clicked
			mouse_hold.insert(mkey);

		if (clicked && !hold) // down when clicked and wasn't hold before
			mouse_down.insert(mkey);

		if (!clicked && hold) // up when not clicked, but was hold
			mouse_up.insert(mkey);
	}
}

GameWindow* Input::getGameWindowPtr()
{
	return game_window;
}

vector<float> Input::getMousePosition()
{
	return {
		mouse_x,
		mouse_y
	};
}

bool Input::isKeyboardPressed(sf::Keyboard::Key key, PressMode mode)
{
	switch (mode) {
	case Hold: return keyboard_hold.find(key) != keyboard_hold.end();
	case Down: return keyboard_down.find(key) != keyboard_down.end();
	case Up: return keyboard_up.find(key) != keyboard_up.end();
	default: return false;
	}
}

bool Input::isMousePressed(sf::Mouse::Button mkey, PressMode mode)
{
	switch (mode) {
	case Hold: return mouse_hold.find(mkey) != mouse_hold.end();
	case Down: return mouse_down.find(mkey) != mouse_down.end();
	case Up: return mouse_up.find(mkey) != mouse_up.end();
	default: return false;
	}
}
