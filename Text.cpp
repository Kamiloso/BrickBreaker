#include "Text.h"
#include "GameWindow.h"

Text::Text(float _x, float _y, const wstring& _text, int _font, sf::Color _color, int _layer)
	: SceneObject(_x, _y, _layer), text(_text), font(_font), color(_color)
{
	
}

void Text::draw(GameWindow* game_window)
{
	sf::RenderWindow& render = game_window->getRenderWindow();

	sf::Text text1;
	text1.setFont(GameWindow::getFont());
	text1.setString(text);
	text1.setCharacterSize(font * 2);
	text1.setScale(0.5f, 0.5f);
	text1.setFillColor(color);

	sf::FloatRect textBounds = text1.getLocalBounds();

	text1.setOrigin(textBounds.width / 2, textBounds.height / 2 + text1.getCharacterSize() / 4.3f);
	text1.setPosition(x, y);

	render.draw(text1);
}
