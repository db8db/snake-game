#include "snake.h"
//#include <iostream>
//#include <ncurses.h>

using namespace std;

int main()
{
//    int r, c;
//    cout << "Choose height of grid: ");
//    //r = getchar();
//    cin >> r;
//    cin.get();
//    cout << "Choose length of grid: ");
//    //c = getchar();
//    cin >> c;
//    cin.get();

    Grid game1(15, 30);
    game1.setup();

    while(!game1.gameover())
    {
        game1.draw();
        if(_kbhit() != 1)
        {
            game1.input(getch123());
        }
        game1.algorithm();
    }

    return 0;
}
