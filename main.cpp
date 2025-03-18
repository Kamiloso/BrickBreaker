#include "GameWindow.h"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    GameWindow GameWindow("Plate Ball Brick - Pre Alpha", settings);
    GameWindow.run(); // Game loop

    return 0;
}