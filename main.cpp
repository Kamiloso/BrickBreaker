#include "GameWindow.h"

using namespace std;

int main()
{
    // Pre-Load assets
    GameWindow::getFont(); // pre-load font

    // Window settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create game window
    GameWindow game_window("Plate Ball Brick - Pre Alpha", settings);
    game_window.run(); // game loop

    return 0;
}