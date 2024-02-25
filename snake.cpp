#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
// void SetClr(int clr)
// {
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
// }

struct position
{
    int ri,ci;
};

enum direction
{
    up,down,Left,Right
};

struct snake
{
    position* ps;
    int size;
    int color;
    direction dir;
    int left_key,right_key,up_key,down_key;
};

void Init (snake& s,int rows,int cols)
{
    s.ps = new position[3] {{rows/2,cols/2},{rows/2,cols/2-1},{rows/2,cols/2-2}};
    s.size = 3;
    s.dir = Right;
}

void display(snake& s,char sym=-37)
{
    CONSOLE_CURSOR_INFO info;											
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});		//	system("cls");

    for (int i = 0; i <s.size; i++)
    {
        gotoRowCol(s.ps[i].ri,s.ps[i].ci);
        cout<<sym;
    }
}

void movesnake(snake& s,int rows,int cols)
{
    for(int i = s.size-1; i-1 >=0 ; i--)
    {
        s.ps[i] = s.ps[i-1];
    }
    switch (s.dir)
    {
        case Right:
            s.ps[0].ci++;
            if (s.ps[0].ci==cols)
                s.ps[0].ci =0;
            break;
        case Left:
            s.ps[0].ci--;
            if (s.ps[0].ci==-1)
                s.ps[0].ci =cols-1;
            break;
        case up:
            s.ps[0].ri--;
            if (s.ps[0].ri==-1)
                s.ps[0].ri =rows-1;
            break;
        case down:
            s.ps[0].ri++;
            if (s.ps[0].ri==rows)
                s.ps[0].ri =0;
            break;
    }
}

void changeDirection(snake& s,int key)
{
    switch (key)
    {
        case 'w':
            if (s.dir == down)
                return;
            s.dir=up;
            break;
        case 's':
            if (s.dir == up)
                return;
            s.dir=down;
            break;
        case 'd':
            if (s.dir == Left)
                return;
            s.dir=Right;
            break;
        case 'a':
            if (s.dir == Right)
                return;
            s.dir=Left;
            break;
    }
}
bool validfood(const position& food, snake& s)
{
    for (int i=0; i<s.size; i++)
    {
        if(s.ps[i].ri == food.ri && s.ps[i].ci == food.ci)
            return false;
    }
    return true;
}
void generatefood(snake& s,position& food,int rows,int cols)
{
    do{
    food.ri=rand()%rows;
    food.ci=rand()%cols;
    }while(!validfood(food,s));
}
void displayfood(position& food)
{
        CONSOLE_CURSOR_INFO info;											
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});		//	system("cls");

    gotoRowCol(food.ri,food.ci);
        cout<<char(3);
}
bool foodEaten(snake& s,position& food)
{
    return s.ps[0].ri == food.ri && s.ps[0].ci == food.ci;
}
void growSnake(snake& s)
{
    position* Ps = new position[s.size + 1];
    for (int i = 0; i < s.size; i++)
    {
        Ps[i] = s.ps[i];
    }
    Ps[s.size] = Ps[s.size - 1];
    delete[] s.ps;
    s.ps = Ps;
    s.size++;
}
int main()
{
    int rows =40,cols =40;
    position food;

    snake s;
    Init(s,rows,cols);
    generatefood(s,food,rows,cols);
    displayfood(food);
    display(s);
    while (true)
    {
        if (_kbhit())
        {
            int key = _getch();
            changeDirection(s,key);
        }
        
        display(s);
        Sleep(50);
        display(s,' ');
        movesnake(s,rows,cols);
        if (foodEaten(s,food))
        {
            growSnake(s);
            generatefood(s,food,rows,cols);
            displayfood(food);
        }
        
    }
    
    return 0;
}