#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class GameWindow //Klasa okna gry
{
public:
	GameWindow(int resolution,string title); //Konstruktor, przyjmuje rozdzielczoœæ i tytu³ okna

	void run(); //Funkcja odpowiedzialna za g³ówn¹ pêtlê gry
	void centerWindow(); //Funkcja zmieniaj¹ca pozycjê okna na centrum ekranu
	void drawCircle(); //Funkcja rysuj¹ca obiekt wykorzystywana w ramach testowania zmiany rozdzielczoœci
	void setView(); //Ustawianie widoku(rozdzielczoœæ jaka jest wyœwietlana) ale nie zmienianie rozmiarów okna

private:
	// wektor rozmiarów ekranu jaki komputer mo¿e przyj¹æ w trybie pe³noekranowym,
	// s³u¿y do ustalania rozdzielczoœci przy tworzeniu okna i ustalaniu rozdzielczoœci przy trybie pe³noekranowym.
	vector<sf::VideoMode> full_screen_resolutions = sf::VideoMode::getFullscreenModes();
	// zmienna odczytuj¹ca dane ekranu,
	// s³u¿y do znalezienia centrum ekranu.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	// wektor mo¿liwych rozdzielczoœci ekranu,
	// s³u¿y do zmiany rozdzielczoœci podczas dzia³ania programu.
	vector<sf::Vector2u> resolutions = {
	{1280,720},
	{1600,900},
	{1920,1080}
	};
	// zmienna która zapisuje jaka jest aktualnie wybrana rozdzielczoœæ. Reprezentuje indeks rozdzielczoœci z wektora resolutions,
	// u¿ywana przy zmianie rozdzielczoœci i przejœciu z trybu pe³noekranowego na tryb w oknie.
	int current_resolution = 3;
	// zmienna która okreœla czy okno jest w³¹czone w trybie pe³noekranowym.
	// u¿ywane przy wchodzeniu i wychodzeniu z fullscreena.
	bool fullscreen = true;
	sf::RenderWindow window;
	void eventHandling(); //Funkcja odpowiedzialna za rozpatrywanie ró¿nych zdarzeñ
	void update(); //Funkcja odpowiedzialna za aktualizowanie stanu gry
	void render(); //Funkcja odpowiedzialna za wyœwietlanie aktualnego stanu gry
};

