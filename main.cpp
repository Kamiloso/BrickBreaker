#include <iostream>
#include "GameWindow.h"
using namespace std;
/*
F-prze³¹czanie trybu pe³noekranowgo
1-rozdzielczoœæ 1280x720
2-rozdzielczoœæ 1600x900
3-rozdzielczoœæ 1920x1080
ESC-wyjœcie z programu

*/



int main()
{

    GameWindow GameWindow(1,"test"); //Stworzenie obiektu okna
    GameWindow.run(); //Pêtla gry


    return 0;
}