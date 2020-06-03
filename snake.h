#ifndef SNAKE_H
#define SNAKE_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
//#include <iostream>

using namespace std;

enum eDirecton {STOP = 0, LEFT, RIGHT, UP, DOWN}; // Controls
//make the game grid 12 x 12

int getch123(void);
int _kbhit();

class Grid
{
public:
    Grid();
    Grid(int r, int c);
    void setup();
    void draw();
    void input(char inputchar);
    void algorithm();
    bool gameover();
private:
    int row;
    int col;
    int x;
    int y;
    eDirecton direction = STOP;
    bool isgameover;
    int fruitX;
    int fruitY;
    int score = 0;
    int nTail = 0;
    int tailX[100];
    int tailY[100];
};

#endif
