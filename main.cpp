#include "GameWindow.h"
#include "Sound.h"
#include "Texture.h"

using namespace std;

int main()
{
    // Sound initialization
    Texture::init();
    Sound::init();
    Sound::setGlobalVolume(0.5f);

    // Window settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create game window
    GameWindow game_window("Plate Ball Brick", settings);
    game_window.run(); // game loop

    return 0;
}