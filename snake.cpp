#include "snake.h"
#include <iostream>
#include <cstdlib>
//#include <ncurses.h>
#include <sys/select.h>

using namespace std;

int _kbhit(void)
{
  struct timeval tv;
  fd_set read_fd;

  /* Do not wait at all, not even a microsecond */
  tv.tv_sec=0;
  tv.tv_usec=0;

  /* Must be done first to initialize read_fd */
  FD_ZERO(&read_fd);

  /* Makes select() ask if input is ready:
   * 0 is the file descriptor for stdin    */
  FD_SET(0,&read_fd);

  /* The first parameter is the number of the
   * largest file descriptor to check + 1. */
  if(select(1, &read_fd,NULL, /*No writes*/NULL, /*No exceptions*/&tv) == -1)
    return 0;  /* An error occured */

  /*  read_fd now holds a bit map of files that are
   * readable. We test the entry for the standard
   * input (file 0). */

if(FD_ISSET(0,&read_fd))
    /* Character pending on stdin */
    return 1;

  /* no characters were pending */
  return 0;
}

int getch123(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

Grid::Grid(): row(10), col(10)
{
    //blank
}

Grid::Grid(int r, int c): row(r), col(c)
{
    //blank
}

void Grid::setup()
{
//    srand(time(0));
    x = col/2;
    y = row/2;
    direction = STOP;
    isgameover = false;
    fruitX = rand() % x;
    fruitY = rand() % y;
}

void Grid::draw()
{
    system("clear");

    for(int i = 0; i < row+2; i++)
    {
        for(int j = 0; j < col+2; j++)
        {
            if(j == col+1)
            {
                cout << "#\n";
            }
            else if(i == 0 ||  j == 0 || i == row+1)
            {
                cout << "#"; //walls
            }
            else if(i == y && j == x)
            {
                cout << "*"; //snake tail
            }
            else if(i == fruitY && j == fruitX)
            {
                cout << "%";
            }
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; k++)
                {
                    if(int(tailX[k]) == j && int(tailY[k]) == i)
                    {
                        cout << "*";
                        print = true;
                    }
                }
                if(!print)
                {
                    cout << " ";
                }
            }
        }
    }
    cout << "\n";
    //(endl);
    cout << "\n";
    //(endl);
    cout << "Score: " << score << "\n";
}

void Grid::input(char inputchar)
{
//    cout << "Enter direction: ";
//    char dir;
//    cin >> dir;
//   switch(dir)
//    string dirstring;
//    dirstring = getch12();
//    char dir = dirstring[0];
    //char dirchar = dir[0];
    //dir = getch();
//    char ch = getchar();
//    cout << "&&&&&&&&\n\n";
//    cout <<  ch;
//    napms(250);

    switch(inputchar)
    {
        case 'a': direction = LEFT; break;
        case 'd': direction = RIGHT; break;
        case 'w': direction = UP; break;
        case 's': direction = DOWN; break;
        case 'x': isgameover = true; break;
    }

//    else
//    {
//        switch(direction)
//        {
//            case 'a': direction = LEFT; break;
//            case 'd': direction = RIGHT; break;
//            case 'w': direction = UP; break;
//            case 's': direction = DOWN; break;
//            case 'x': isgameover = true; break;
//        }
//    }
    usleep(250000);

}

void Grid::algorithm()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int nextX, nextY;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; i++)
    {
        nextX = tailX[i];
        nextY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = nextX;
        prevY = nextY;
    }

    switch(direction)
    {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    for(int i = 0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            isgameover = true;
    }

    if(x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % x;
        fruitY = rand() % y;
        nTail++;
    }
}

bool Grid::gameover()
{
    return isgameover;
}


