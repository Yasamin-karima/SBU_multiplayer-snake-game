#include <iostream>
#include <string>
#include "structs.hpp"
#include "clui.h"


int dly; //delay
int GameState;
// 1:homePage  2:startNewGame  3:continuePlaying
// 4:leaderBoard  5:p1 wins  6:p2 wins
// 7:p3 wins  8:no one win   9: two players win
// 10:start gamebord
player PLAYER[5];
int ActiveP;
int activeP[4];
int noOfPlayers;
const int height = 30;
const int width = 100;
bool isGameOver;
int noOfFruits;
Fruit fruit[5];
char FRUIT = 5;
int noOfBombs;
Bomb bomb[5];
char BOMB = 2;


void clear ()
{
    save_cursor();
    std::cout << "     ";
    restore_cursor();
}
void changeColorToDefault()
{
    change_color_rgb(246, 253, 195);
}
void changeColorToWHITE()
{
    change_color_rgb(249, 239, 219);
}
void changeColorToRED()
{
    change_color_rgb(255, 128, 128);
}
void changeColorToORANGE()
{
    change_color_rgb(255, 215, 150);
}
void changeColorToGREEN()
{
    change_color_rgb(205, 250, 213);
}
void swap (player &p1, player &p2)
{
    player temp=p1; p1=p2; p2=temp;
}
void bubbleSort (player* pArr, int size) //pArr : player array
{
    for (int i=0; i<size-1; i++)
    {
        for (int j=1; j<=size-i-1; j++)
        {
            if (pArr[j].score < pArr[j+1].score)
            {
                swap (pArr[j+1], pArr[j]);
            } else continue;
        }
    }
}

void welcome()
{
    cursor_to_pos(1, 40);
    changeColorToRED();
    std::cout << "WELCOME =]" << std::endl;
    cursor_to_pos(2, 40);
    changeColorToGREEN();
    std::cout << "Let's Start The Game" << std::endl;
    cursor_to_pos(3, 40);
    std::cout << "Enter Players' Informations..." << std::endl;
    changeColorToWHITE();
}

void showModeMenu()
{
    changeColorToORANGE();
    save_cursor();
    std::cout << std::endl << "          ";
    std::cout << "(1) single player" << "          ";
    std::cout << "(2) two players" << "          ";
    std::cout << "(3) three players" ;
    restore_cursor();
    changeColorToWHITE();
}
void defineNoOfplayer ()
{
    int n;
    bool invalid;
    do {
        invalid = false;
        save_cursor();
        std::cin >> n;

        switch (n)
        {
            case 1:
                noOfPlayers=1; ActiveP= 1;
                break;
            case 2:
                noOfPlayers=2; ActiveP= 2;
                break;
            case 3:
                noOfPlayers=3; ActiveP= 3;
                break;
            default:
                cursor_to_pos(7, 1);
                std::cout << "enter a valid number";
                restore_cursor();
                clear();
                invalid = true;
                break;
        }
    } while (invalid);
}
void howManyPlayers ()
{
    changeColorToWHITE();
    cursor_to_pos(5, 1);
    std::cout << "CHOOSE GAME MODE : ";
    showModeMenu();
    defineNoOfplayer();
}

void showColorMenu(int Y)
{
    cursor_to_pos(Y,1);
    changeColorToORANGE();
    std::cout << "NOTE : you will be surprised by colors :)" << std::endl;
    std::cout << "(1) green" << std::endl;
    std::cout << "(2) blue" << std::endl;
    std::cout << "(3) red" << std::endl;
    std::cout << "(4) purple" << std::endl;
    std::cout << "(5) yellow" << std::endl;
    std::cout << "(6) orange" << std::endl;
    std::cout << "(7) pink" << std::endl;
    std::cout << "(8) white" << std::endl; 
    changeColorToWHITE();
}
void showChosenColor(player p)
{
    std::cout << "YOU CHOSE : ";
    change_color_rgb(p.color.r, p.color.g, p.color.b);
    std::cout << p.color.name;
}
void defineColor ( player &p)
{
    int color;
    bool invalid;
    do {
        invalid = false;
        save_cursor();
        std::cin >> color;

        switch (color)
        {
            case 1: 
                p.color.r=153 ; p.color.g=188 ; p.color.b=133 ;
                p.color.name="green"; break;
            case 2: 
                p.color.r=104 ; p.color.g=149 ; p.color.b=210 ;
                p.color.name="blue"; break;
            case 3: 
                p.color.r=254 ; p.color.g=0 ; p.color.b=0 ;
                p.color.name="red"; break;
            case 4: 
                p.color.r=216 ; p.color.g=180 ; p.color.b=248 ;
                p.color.name="purple"; break;
            case 5: 
                p.color.r=255 ; p.color.g=247 ; p.color.b=138 ;
                p.color.name="yellow"; break;
            case 6: 
                p.color.r=236 ; p.color.g=143 ; p.color.b=94 ;
                p.color.name="orange"; break;
            case 7: 
                p.color.r=251 ; p.color.g=161 ; p.color.b=183 ;
                p.color.name="pink"; break;
            case 8: 
                p.color.r=243 ; p.color.g=238 ; p.color.b=234 ;
                p.color.name="white"; break;
            default:
                cursor_to_pos(22, 1);
                std::cout << "Please enter a valid number";
                restore_cursor();
                clear();
                invalid = true;
                break;
            }
    } while (invalid);
}

void getName(player &p)
{
    change_color_rgb(p.color.r, p.color.g, p.color.b);
    std::cin >> p.name;
}

void getPlayerInfoNew(player* p, int num)
{
    int start = 20 + 4*num;
    cursor_to_pos(start, 1);
    changeColorToWHITE(); 
    std::cout << "ENTER PLAYER " << num << " COLOR : ";
    defineColor(p[num]);
    
    cursor_to_pos(start+1, 1);
    showChosenColor(p[num]);

    cursor_to_pos(start+2, 1);
    changeColorToWHITE();
    std::cout << "ENTER PLAYER " << num << " NAME : ";
    getName(p[num]);
}

void showSpeedMenu()
{
    changeColorToORANGE();
    save_cursor();
    std::cout << std::endl << "          ";
    std::cout << "(1) slow" << "          ";
    std::cout << "(2) medium" << "          ";
    std::cout << "(3) fast" ;
    restore_cursor();
    changeColorToWHITE();
}
void defineSpeed ()
{
    int speed;
    bool invalid ;
    do {
        invalid = false;
        save_cursor();
        std::cin >> speed;

        switch (speed)
        {
            case 1:
                dly = 100; break;
            case 2:
                dly = 50; break;
            case 3:
                dly = 10; break;
            default:
                cursor_to_pos(11, 1);
                std::cout << "enter a valid number";
                restore_cursor();
                clear();
                invalid = true;
                break;
        }
    } while (invalid);
}
void chooseSpeed (int Y)
{
    cursor_to_pos(Y, 1);
    changeColorToWHITE();
    std::cout << "CHOOSE GAME SPEED : ";
    showSpeedMenu();
    defineSpeed();
}

void drawWalls()
{
    for (int i=0; i<width/2; i++)
    {
        std::cout << 'S' << ' '; 
    } std::cout << std::endl;
    
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (j==0 || j==width-1)  
            {
                cursor_to_pos(i, j);
                std::cout << 'S';
            } else continue;
        } std::cout << std::endl;  
    }

    for (int i=0; i<width/2; i++)
    {
        std::cout << 'S' << ' '; 
    } std::cout << std::endl;
}
void setSnakeAtFirst(player &p, int num, int inGamePlyrs)
{
    p.snake.nTail = 4;

    p.snake.headX = width - num * width / (1+inGamePlyrs);
    p.snake.headY = height/2;      

    p.snake.tailX[0] = p.snake.headX;
    p.snake.tailY[0] = p.snake.headY;

    p.snake.tailX[1] = p.snake.headX; 
    p.snake.tailY[1] = p.snake.headY + 1;

    p.snake.tailX[2] = p.snake.headX; 
    p.snake.tailY[2] = p.snake.headY + 2;

    p.snake.tailX[3] = p.snake.headX; 
    p.snake.tailY[3] = p.snake.headY + 3;
}
void drawSnake(player p)
{
    change_color_rgb(p.color.r, p.color.g, p.color.b);
    cursor_to_pos(p.snake.tailY[0], p.snake.tailX[0]);
    std::cout << 'O';
    for (int i=1; i<=p.snake.nTail; i++)
    {
        cursor_to_pos(p.snake.tailY[i], p.snake.tailX[i]);
        std::cout << 'o';
    }
    reset_color();
}
void clearSnake (player p)
{
    cursor_to_pos( p.snake.tailY[p.snake.nTail] , p.snake.tailX[p.snake.nTail]);
    std::cout << ' ';
}


void showScore(player p)
{
    cursor_to_pos(32, p.snake.headX-10);
    change_color_rgb(p.color.r, p.color.g, p.color.b);
    std::cout << p.name << " : " << p.score;
}

void setFruitsAtFirst(int activeP)
{
    noOfFruits=activeP;
    for (int i=0; i<noOfFruits; i++)
    {
        fruit[i].X = rand() % width;
        fruit[i].Y = rand() % height;
    }
}
void setBombsAtFirst(int activeP)
{
    noOfBombs=activeP;
    for (int i=0; i<noOfBombs; i++)
    {
        bomb[i].X = (rand() % width) / 2; // divided by two, not to be
        bomb[i].Y = (rand() % height) / 2;// at same place as fruit is
    }
}

void drawFruits()
{
    for (int i=0; i<noOfFruits; i++)
    {
        cursor_to_pos(fruit[i].Y, fruit[i].X);
        change_color_rgb(141, 223, 203);
        std::cout << FRUIT;
    }
}
void drawBombs()
{
    for (int i=0; i<noOfBombs; i++)
    {
        cursor_to_pos(bomb[i].Y, bomb[i].X);
        change_color_rgb(120, 122, 145);
        std::cout << BOMB;
    }
}

void defineKey1(player &p, int key)
{
    if (key==224 || key==0) {
        do {
            key=getch();
        } while(key==224 || key==0);

        switch (key) {
            case 72: // up
               p.dir = UP;
                 break;
            case 75: // left
                p.dir = LEFT;
                 break;
            case 77:// right
                p.dir = RIGHT;
                 break;
            case 80: // down
                p.dir = DOWN;
                 break;
            default :
                break;
        }
    }
}
void defineKey2(player &p, int key)
{
    switch (key)
    {
    case 'H': case 'h':
       p.dir = UP;
        break;
    case 'N': case 'n':
        p.dir = DOWN;
        break;
    case 'B': case 'b':
        p.dir = LEFT;
        break;
    case 'M': case 'm':
        p.dir = RIGHT;
        break;
    
    default:
        break;
    }
}
void defineKey3(player &p, int key)
{
    switch (key)
    {
    case 'W': case 'w':
       p.dir = UP; 
        break;
    case 'S': case 's':
        p.dir = DOWN;
        break;
    case 'A': case 'a':
        p.dir = LEFT;
        break;
    case 'D': case 'd':
        p.dir = RIGHT;
        break;
    
    default:
        break;
    }
}
void moveHead (player &p)
{
    switch (p.dir)
    {
    case UP:
        p.snake.tailY[0]--;
        break;
    case DOWN:
        p.snake.tailY[0]++;
        break;
    case RIGHT:
        p.snake.tailX[0]++;
        break;
    case LEFT:
        p.snake.tailX[0]--;
        break;
    
    default:
        break;
    }
}
void letTailFollow(player &p)
{
    for (int i = p.snake.nTail; i>0; i--)
    {
        p.snake.tailX[i] = p.snake.tailX[i-1];
        p.snake.tailY[i] = p.snake.tailY[i-1];
    }
}

void checkWhoWins (int num, int code) // code 0 is for general lose, 1:if two snakes hit their heads
{
    if (code!=0) // 
    {
        if (ActiveP==2)
        {
            GameState=8; 
        } else if (ActiveP==3) {
            switch (num)
            {
            case 1:
                switch (code)
                {
                case 2:
                    GameState=7; break; 
                case 3:
                    GameState=6; break; 
                default:
                    break;
                }
                break;
            case 2:
                switch (code)
                {
                case 1:
                    GameState=7; break;
                case 3:
                    GameState=5; break;
                default:
                    break;
                }
                break;
            case 3:
                switch (code)
                {
                case 2:
                    GameState=5; break;
                case 1:
                    GameState=6; break;
                default:
                    break;
                }
                break;
            
            default:
                break;
            }

        }
    } else {
        if (ActiveP==1)
        {
            GameState=8;
        } else if (ActiveP==2)
        {
            (num==1) ? GameState=6 : GameState=5;
        } else if (ActiveP==3)
        {
            switch (num)
            {
            case 1:
                if (PLAYER[2].score==PLAYER[3].score)
                    GameState=9;
                (PLAYER[2].score>PLAYER[3].score) 
                    ? GameState=6
                    : GameState=7;
                break;
            case 2:
                if (PLAYER[1].score==PLAYER[3].score)
                    GameState=9;
                (PLAYER[1].score>PLAYER[3].score) 
                    ? GameState=5
                    : GameState=7;
                break;
            case 3:
                if (PLAYER[2].score==PLAYER[1].score)
                    GameState=9;
                (PLAYER[2].score>PLAYER[1].score) 
                    ? GameState=6
                    : GameState=5;
                break;
            
            default:
                break;
            }
        }
    }
    
}
void checkWallHit (player p, int num)
{
    if (p.snake.tailX[0]==1 || 
        p.snake.tailX[0]==width-1 ||
        p.snake.tailY[0]==1 || 
        p.snake.tailY[0]==30 ) //  p loses, more score wins
    {
        checkWhoWins(num, 0);
        isGameOver = true;
    }
}
void checkBombHit (player p, int num)
{
    for (int i=0; i<noOfBombs; i++)
    {
        if (bomb[i].X == p.snake.tailX[0] &&
            bomb[i].Y == p.snake.tailY[0])
        {
            checkWhoWins(num, 0);
            isGameOver = true; // p loses and more score wins
        }
    }
}
void checkSnakesHit (player p, int num) // others and it's own tail
{
    for (int i=1; i<=ActiveP; i++)
    {
        for (int j=1; j<PLAYER[activeP[i]].snake.nTail; j++)
        {
            if (p.snake.tailX[0]==PLAYER[activeP[i]].snake.tailX[j] && 
                p.snake.tailY[0]==PLAYER[activeP[i]].snake.tailY[j] ) // p loses the game, more cscore wins
            {
                checkWhoWins(num, 0);
                isGameOver = true;
            } 
        }
        if (i!=num)
        {
            if (p.snake.tailX[0]==PLAYER[activeP[i]].snake.tailX[0] && 
                p.snake.tailY[0]==PLAYER[activeP[i]].snake.tailY[0] ) // p & player[i] lose the game, the other one wins
            {
                checkWhoWins(num, activeP[i]);
                isGameOver = true;
            }
        }
    }
}
void checkGameOver(player p, int num)
{
    checkWallHit(p, num);
    checkSnakesHit(p, num);
    checkBombHit(p, num);   
}
void checkEatFruit (player &p)
{
    for (int i=0; i<noOfFruits; i++)
    {
        if (p.snake.tailX[0] == fruit[i].X &&
            p.snake.tailY[0] == fruit[i].Y)
        {
            p.score += 5;
            p.snake.nTail++;
            fruit[i].X = rand() % width;
            fruit[i].Y = rand() % height;

            noOfBombs++;
            bomb[i].X = (rand() % width) / 2; 
            bomb[i].Y = (rand() % height) / 2;
        }
    }
}

int checkWhoHasLoggedIn ()
{
    char temp[20];
    std::cin >> temp;
    for (int i=1; i<=noOfPlayers; i++)
    {
        if (strcmp(temp, PLAYER[i].name)==0)  // means this player has already logged in
        {
            return i;
        }  
    }
    return 0;
}

void showOptions()// for home page
{
    changeColorToORANGE();
    save_cursor();
    cursor_to_pos(10, 35);
    std::cout << "(1) Start New Game" << std::endl;
    cursor_to_pos(11, 35);
    std::cout << "(2) Continue Playing" << std::endl;
    cursor_to_pos(12, 35);
    std::cout << "(3) Leader Board" << std::endl;
    cursor_to_pos(13, 35);
    std::cout << "(4) Learn How To Play" << std::endl;
    cursor_to_pos(14, 35);
    std::cout << "(5) Press <esc> To Exit Program" << std::endl;
    restore_cursor();
    changeColorToWHITE();
}

void ShowScoreLDRBRD(player p, int num) // name is abbr of : score in leaderboard
{
    cursor_to_pos(num*2+2, 26);
    changeColorToGREEN();
    std::cout << '-' << num << '-';

    change_color_rgb(p.color.r, p.color.g, p.color.b);
    std::cout << "     " << p.name;
    cursor_to_pos(num*2+2, 50);
    std::cout << p.score;
    cursor_to_pos(num*2+2, 60);
    std::cout << p.win;
}

bool checkControlKeyHits()
{
    switch (getch())
    {
    case 27:
        GameState=15; return true; // esc for exit program
    case 32:
        GameState=1; return true; // space for home page

    default:
        return false;
        break;
    }
    
}

