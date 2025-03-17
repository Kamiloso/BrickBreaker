#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class GameWindow //Klasa okna gry
{
public:
	GameWindow(int resolution,string title); //Konstruktor, przyjmuje rozdzielczo�� i tytu� okna

	void run(); //Funkcja odpowiedzialna za g��wn� p�tl� gry
	void centerWindow(); //Funkcja zmieniaj�ca pozycj� okna na centrum ekranu
	void drawCircle(); //Funkcja rysuj�ca obiekt wykorzystywana w ramach testowania zmiany rozdzielczo�ci
	void setView(); //Ustawianie widoku(rozdzielczo�� jaka jest wy�wietlana) ale nie zmienianie rozmiar�w okna

private:
	// wektor rozmiar�w ekranu jaki komputer mo�e przyj�� w trybie pe�noekranowym,
	// s�u�y do ustalania rozdzielczo�ci przy tworzeniu okna i ustalaniu rozdzielczo�ci przy trybie pe�noekranowym.
	vector<sf::VideoMode> full_screen_resolutions = sf::VideoMode::getFullscreenModes();
	// zmienna odczytuj�ca dane ekranu,
	// s�u�y do znalezienia centrum ekranu.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	// wektor mo�liwych rozdzielczo�ci ekranu,
	// s�u�y do zmiany rozdzielczo�ci podczas dzia�ania programu.
	vector<sf::Vector2u> resolutions = {
	{1280,720},
	{1600,900},
	{1920,1080}
	};
	// zmienna kt�ra zapisuje jaka jest aktualnie wybrana rozdzielczo��. Reprezentuje indeks rozdzielczo�ci z wektora resolutions,
	// u�ywana przy zmianie rozdzielczo�ci i przej�ciu z trybu pe�noekranowego na tryb w oknie.
	int current_resolution = 3;
	// zmienna kt�ra okre�la czy okno jest w��czone w trybie pe�noekranowym.
	// u�ywane przy wchodzeniu i wychodzeniu z fullscreena.
	bool fullscreen = true;
	sf::RenderWindow window;
	void eventHandling(); //Funkcja odpowiedzialna za rozpatrywanie r�nych zdarze�
	void update(); //Funkcja odpowiedzialna za aktualizowanie stanu gry
	void render(); //Funkcja odpowiedzialna za wy�wietlanie aktualnego stanu gry
};

