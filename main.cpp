#include <iostream>
#include "GameWindow.h"
using namespace std;
/*
F-prze��czanie trybu pe�noekranowgo
1-rozdzielczo�� 1280x720
2-rozdzielczo�� 1600x900
3-rozdzielczo�� 1920x1080
ESC-wyj�cie z programu

*/



int main()
{

    GameWindow GameWindow(1,"test"); //Stworzenie obiektu okna
    GameWindow.run(); //P�tla gry


    return 0;
}