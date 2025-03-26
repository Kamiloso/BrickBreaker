#include "GameWindow.h"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    GameWindow game_window("Plate Ball Brick - Pre Alpha", settings);
    game_window.run(); // Game loop

    return 0;
}