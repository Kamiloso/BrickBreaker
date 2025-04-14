#include "GameWindow.h"
#include "Sound.h"

using namespace std;

int main()
{
    // Sound initialization
    Sound::init();
    Sound::setGlobalVolume(80.f);

    // Window settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create game window
    GameWindow game_window("Plate Ball Brick", settings);
    game_window.run(); // game loop

    return 0;
}