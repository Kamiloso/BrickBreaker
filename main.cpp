#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
    cout << "Czeœæ trochê to zmieni³em!" << endl;
    for (int i = 0; i < 100; i++)
        cout << "Po co sie ograniczac?" << endl;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    system("pause");

    return 0;
}