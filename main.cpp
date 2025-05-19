#include "GameWindow.h"
#include "Sound.h"
#include "Texture.h"

#include <iostream>

using namespace std;

int main()
{
    // Static class initialization
    Texture::init();
    Sound::init();

    // Window settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create game window
    GameWindow game_window("Brick Breaker", settings);
    game_window.run(); // game loop

    return 0;
}