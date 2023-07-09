//                              code by mamba
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

bool gameover, walls;
const int height = 20;
const int width = 20;
int snake_x,snake_y, fruit_x, fruit_y, score, speed;
int tail_x[400], tail_y[400];
int tail;
enum direction {stop=0, Left,Right,up,down};
direction directi;

void instruction()
{
	string myName;
	char option;

	cout << "What is your name?" << endl;
    getline(cin, myName); 
    again:
    system("cls");
	cout << "***************************************************" << endl;
	cout << " " << endl;
    cout << "                 Welcome, " << myName << "!" << endl;
  	cout << " " << ::endl;
    cout << "Please choose a letter for the difficulty you want:" << endl;
    cout << " " << endl;
    cout << "A) Newbie             (No walls, low speed)" << endl;
    cout << "B) Rokiee             (walls, medium speed)" << endl;
    cout << "C) Expert             (walls, high speed)" << endl;
    cout << " " << endl;
    cout << "***************************************************" << endl;
    cout << "Your option : ";
    cin >> option;
    option = toupper(option);

    switch (option)
    {
    	case 'A':
    	    speed = 200;
            walls = false;
    	    break;
    	case 'B':
    	    speed = 100;
            walls = true;
    	    break;
    	case 'C':
    	    speed = 20;
            walls = true;
    	    break;
    	default:
            goto again;
    	    break;
    }
	system("cls");
}

void setup()
{
    gameover = false;
    directi = stop;
    snake_x = width / 2 ;
    snake_y = height / 2;
    srand(time(0));
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    score = 0;

}

void Draw()
{
    CONSOLE_CURSOR_INFO info;											
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});		//	system("cls");
    for (int i = 0; i <= width+2; i++)
        cout<<"#";
    cout<<"\n";
    for (int i = 0; i < width+1; i++)
    {
        for (int j = 0; j <= width+1; j++)
        {
            if (j == 0)
                cout<<"#";
            if (j == width+1)
                cout<<"#";
            if (i == snake_x && j == snake_y)
                cout<<"O";
            else if (i == fruit_x && j == fruit_y)
                cout<<"*";
            else
            {
                bool print = false;
                for (int k = 0; k < tail; k++)
                {
                    if (tail_x[k] == i && tail_y[k] == j )
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if (!print)
                    cout<<" ";
            }           
        }
        cout<<"\n";
    }
    
    for (int i = 0; i <= width+2; i++)
        cout<<"#";
    cout << "\n";
    cout << "Score : "<<score<<"\n";
    
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
            if(directi == down)
                break;
            directi=up;
            break;
        case 's':
            if(directi == up)
                break;
            directi=down;
            break;
        case 'a':
            if(directi == Right)
                break;
            directi=Left;
            break;
        case 'd':
            if(directi == Left)
                break;
            directi=Right;
            break;
        case 'p':
            gameover = true;
            break;
        }
    }
    

}

void logic()
{
                // afer snake eating food :
    if (snake_x == fruit_x && snake_y == fruit_y)
    {
        score += 10; 
        fruit_x = rand() % width;
        fruit_y = rand() % height;
        tail++;
    }

                    // tail increase :
    for (int i = tail; i > 0; i--)
    {
        tail_x[i] = tail_x[i-1];
        tail_y[i] = tail_y[i-1];
    }
    tail_x[0] = snake_x;
    tail_y[0] = snake_y;
    
                    // movement :
    switch (directi)
        {
        case up:
            snake_x--;
            break;
        case down:
            snake_x++;
            break;
        case Left:
            snake_y--;
            break;
        case Right:
            snake_y++;
            break;
        }

                        // snake touch border :
    if (walls)
    {
        if (snake_x > width || snake_x < 0 || snake_y > height || snake_y < 0)
            gameover = true;
    }

    if (!walls)
    {
        if (snake_x > width)
            snake_x = 0;
        else if( snake_x < 0) 
            snake_x = width - 1;
        else if (snake_y > height)
            snake_y = 0; 
        else if (snake_y < 0)
            snake_y = height - 1;
        
    }

                        // snake body :
    for (int i = 0; i < tail; i++)
        if (tail_x[i] == snake_x && tail_y[i] == snake_y)
            gameover = true;
    
}

int main()
{
    instruction();
    setup();
    while (!gameover)
    {
        Draw();
        input();
        logic();
        Sleep(speed);
    }
    
    return 0;
}
