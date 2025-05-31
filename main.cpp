#include "GameWindow.h"
#include "Sound.h"
#include "Texture.h"

#include <iostream>

// For console hiding (only Windows)
#if defined(_WIN32) && defined(NDEBUG)
#include <windows.h>
#endif

using namespace std;

int main()
{
    // Hide console (only Windows)
#if defined(_WIN32) && defined(NDEBUG)
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
#endif

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