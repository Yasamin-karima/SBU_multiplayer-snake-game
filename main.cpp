
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <string>
#include "clui.h"
#include "functions.hpp"
#include "structs.hpp"

using namespace std;


std::queue<int> keysPressed;


void ShowFooter()
{
    changeColorToDefault();
    cursor_to_pos(35, 1);
    for (int i=0; i<width; i++)
    {
        std::cout << '_' << endl;
    }
    std::cout << "PRESS : ";
    
}

void howToPlay ()
{
    clear_screen();
    changeColorToGREEN();
    string line;
    ifstream myfile ("howtoplay.txt");
    if (myfile.is_open())
    {

    while(getline(myfile, line)) {
      std::cout << line << endl;
    }
    myfile.close();
    } else return;    

    if (checkControlKeyHits())
            {
                return;
            }

}

void getMove(player &p, int num)
{
    if (kbhit())
    {
        int key = nb_getch();
        keysPressed.push(key);
    }

    if (!keysPressed.empty())
    {
        int key = keysPressed.front();
        keysPressed.pop();
        switch (num)
        {
        case 1:
            defineKey1(p, key); //PLAYER[1]
            break;
        case 2:
            defineKey2(p, key); //PLAYER[2]
            break;
        case 3:
            defineKey3(p, key); //PLAYER[3]
            break;
        
        default:
            break;
        }
    }
    if (p.dir!=STOP)
    {
        letTailFollow(p);
        moveHead(p);
    } 
}
void gameBoardContinue (int &p1, int &p2, int &p3) // index of active player in PLAYER array
{
    clear_screen();
    changeColorToWHITE();
    drawWalls();
    // showHints();
    isGameOver = false;
    
    while(!isGameOver)
    {
        if (p1!=0)
        {
        drawFruits();
        drawBombs();
        drawSnake(PLAYER[p1]);
        clearSnake(PLAYER[p1]);
        showScore(PLAYER[p1]);
        checkGameOver(PLAYER[p1], 1);
        getMove(PLAYER[p1], 1);
        checkEatFruit(PLAYER[p1]);
        }

        if (p2!=0)
        {
            drawFruits();
            drawBombs();
            drawSnake(PLAYER[p2]);
            clearSnake(PLAYER[p2]);
            showScore(PLAYER[p2]);
            checkGameOver(PLAYER[p2], 2);
            getMove(PLAYER[p2], 2);
            checkEatFruit(PLAYER[p2]);
        }

        if (p3!=0)
        {
            drawFruits();
            drawBombs();
            drawSnake(PLAYER[p3]);
            clearSnake(PLAYER[p3]);
            showScore(PLAYER[p3]);
            checkGameOver(PLAYER[p3], 3);
            getMove(PLAYER[p3], 3);
            checkEatFruit(PLAYER[p3]);
        }
        
        
        
        delay (dly);
    }
    p1=0; p2=3; p3=0;
    ActiveP=0; 

    if (checkControlKeyHits())
            {
                return;
            }
}

void gameBoardNew ()
{
    clear_screen();
    changeColorToWHITE();
    drawWalls();
    // showHints();
    isGameOver = false;
    
    while(!isGameOver)
    {
        for (int i=1; i<=noOfPlayers; i++)
        { 
            drawFruits();
            drawBombs();
            drawSnake(PLAYER[i]);
            clearSnake(PLAYER[i]);
            showScore(PLAYER[i]);
            cursor_to_pos(0,0);
            checkGameOver(PLAYER[i], i);
            getMove(PLAYER[i], i);
            checkEatFruit(PLAYER[i]);
        }
        delay (dly);
    }

    ActiveP=0;


    if (checkControlKeyHits())
            {
                return;
            }
}

void showNoPlayerWon ()
{
    clear_screen();
    cursor_to_pos(5, 10);
    changeColorToRED();
    std::cout << "NON OF PLAYERS WON :(" << endl;
    for (int i=1; i<=noOfPlayers; i++)
    {
        cursor_to_pos(i*2+6, 10);
        change_color_rgb(PLAYER[i].color.r, PLAYER[i].color.g, PLAYER[i].color.b);
        std::cout << PLAYER[i].name << " : " << PLAYER[i].score;
    }

    if (checkControlKeyHits())
            {
                return;
            }
}

void showPlayerWon (player &p)
{
    p.score += 10; // player will get 10 points if they win a game.

    clear_screen();
    cursor_to_pos(5, 37);
    changeColorToRED();
    std::cout << (char) 4 << "  " << (char) 30 << "  ";
    change_color_rgb(p.color.r, p.color.g, p.color.b);
    std::cout << p.name << "WON";
    changeColorToRED();
    std::cout << "  " << (char) 30 << "  " << (char) 4 ;
    cursor_to_pos(7, 40);
    changeColorToGREEN();
    std::cout << p.name << "'s score : " << p.score;

    p.win++;

}

void leaderBoard ()
{
    clear_screen();
    changeColorToRED();
    cursor_to_pos(1, 40);
    std::cout << "|<| LEADER BOARD |>|";

    cursor_to_pos(2, 25);
    for (int i = 0; i < width/4; i++)
        std::cout << ">";
    std::cout << ' ';
    for (int i = 0; i < width/4; i++)
        std::cout << "<";
    cursor_to_pos(3, 35);
    changeColorToORANGE();
    std::cout << "name";
    cursor_to_pos(3, 50);
    std::cout << "score";
    cursor_to_pos(3, 60);
    std::cout << "won games";

    bubbleSort(PLAYER, noOfPlayers);
    for (int i=1; i<=noOfPlayers; i++)
    {
        cursor_to_pos(i*2+2, 35);
        ShowScoreLDRBRD(PLAYER[i], i);
    }
    if (checkControlKeyHits())
            {
                return;
            }
    
}

void getPlayerInfoContinue (player &newP, int num)
{ 
    changeColorToWHITE(); 
    std::cout << "ENTER PLAYER " << num << " COLOR : ";
    defineColor(newP);
    
    showChosenColor(newP);

    std::cout << endl;
    changeColorToWHITE();
    std::cout << "ENTER PLAYER " << num << " NAME : ";
    getName(newP);
}
void continuePlaying ()
{
    clear_screen();
    {
    cursor_to_pos(2, 47);
    changeColorToRED();
    std::cout << "HI AGAIN ^_~" << endl;
    cursor_to_pos(4, 47);
    changeColorToGREEN();
    std::cout << "You Can Continue Playing" <<endl;
    cursor_to_pos(5, 47);
    std::cout << "With Your Previous Players" <<endl;
    cursor_to_pos(6, 47);
    std::cout << "Or New Players" <<endl;
    }
    changeColorToWHITE();
    std::cout << endl << "CHOOSE GAME MODE : ";
    showModeMenu();
    bool ColorMenuShown=false;
    int n;
    cin >> n;
    ActiveP=n;
    for (int i=1; i<=n; i++)
    {   
        changeColorToWHITE();
        std::cout << endl << endl << "ENTER USERNAME : ";
        int userNum = checkWhoHasLoggedIn();
        if (userNum!=0) // this player has already logged in
        {
            change_color_rgb(PLAYER[userNum].color.r, PLAYER[userNum].color.g, PLAYER[userNum].color.b);
            std::cout << "          " << "Hello " << PLAYER[userNum].name << " My Old Friend :)" << endl;
            activeP[i]=userNum;
            setSnakeAtFirst(PLAYER[userNum], i, ActiveP);
        } else {
            noOfPlayers++;
            int indexNew=noOfPlayers;
            std::cout << endl << endl;
            
            if (!ColorMenuShown)
            {
                showColorMenu(get_cursor_x());
                std::cout << endl;
                ColorMenuShown=true;
            }

            getPlayerInfoContinue(PLAYER[indexNew], indexNew);
            activeP[i]=indexNew;
            setSnakeAtFirst(PLAYER[indexNew], i, ActiveP);
        }
    }
    std::cout << endl << endl;
    chooseSpeed(get_cursor_x());

    setFruitsAtFirst(ActiveP);
    setBombsAtFirst(ActiveP);
    

    std::cout << endl << endl << "Press Enter to start the game...";
    
    if (getch()==13)
    {
        GameState=11;
    }
    if (checkControlKeyHits())
    {
        return;
    }
}

void startNewGame ()
{
    clear_screen();
    welcome();
    howManyPlayers();
    chooseSpeed(9);
    showColorMenu(13); 
    for (int i=1; i<=noOfPlayers; i++)
    { 
        getPlayerInfoNew(PLAYER, i);
        setSnakeAtFirst(PLAYER[i], i, noOfPlayers); 
    }
    setFruitsAtFirst(noOfPlayers);
    setBombsAtFirst(noOfPlayers);
    changeColorToWHITE();
    std::cout << endl << "Press Enter to start the game...";
    
    while (GameState!=10){
        if (getch()==13)
        {
            GameState=10;
        }
    }
    if (checkControlKeyHits())
            {
                return;
            }
}

void showHomePage()
{
    clear_screen();
    cursor_to_pos(3, 49);
    changeColorToRED();
    std::cout << "HELLO" << endl;
    cursor_to_pos(5, 35);
    changeColorToGREEN();
    std::cout << "WE ARE ABOUT TO PLAY A SNAKE GAME :)" << endl;
    cursor_to_pos(6, 35);
    std::cout << "ARE YOU READY?  LET'S START IT..." << endl;
    cursor_to_pos(8, 35);
    changeColorToWHITE();
    std::cout << "Choose : ";

    showOptions();
    if (checkControlKeyHits())
            {
                return;
            }
}
void homeInMain () // remember its a main function
{
    showHomePage();
    int choiceH; //choice for home page
    bool invalid;
    do {
        
        invalid = false;
        cin >> choiceH;
        switch (choiceH)
        {
            case 1:
                GameState=2; // start new game; 
                break;
            case 2:
                GameState=3; // continue playing; 
                break;
            case 3:
                GameState=4; // leaderboard
                break;
            case 4:
                GameState=14;// how to play
                break; 
            case 5:
                GameState=15; // exit
                break;
            default: 
                cursor_to_pos(15, 35);
                changeColorToWHITE();
                std::cout << "Enter a valid number" << endl;
                restore_cursor();
                clear();
                invalid = true;
                break;
        }
    } while (invalid);
    if (checkControlKeyHits())
            {
                return;
            }
}

// 1:showHomePage  2:startNewGame  3:continuePlaying
// 4:leaderBoard  5:p1 wins  6:p2 wins
// 7:p3 wins  8:no one win   9: two players win
// 10:start gameboard  11: gameboard continue


int main () {

    init_clui();
    GameState = 1;

    while (getch()!=27)
    {
        if (getch()==32)
        {
            GameState=1;
        }
        switch (GameState)
        {
        case 1:
            homeInMain() ; break;
        case 2:
            startNewGame(); break;
        case 3:
            continuePlaying(); break;
        case 5:
            // showPlayerWon(PLAYER[activeP[1]]);
            leaderBoard() ; break;  //p1 wins;
        case 6:
            // showPlayerWon(PLAYER[activeP[2]]);
            leaderBoard() ; break; //p2 wins;
        case 7:
            // showPlayerWon(PLAYER[activeP[3]]);
            leaderBoard() ; break; //p3 wins;
        case 4:
            leaderBoard() ; break;
        case 8:
            showNoPlayerWon(); break; // no one wins;
        case 9:
            // two players win; 
            break;
        case 10:
            gameBoardNew(); break;//playing game in new game
        case 11:
            gameBoardContinue (activeP[1], activeP[2], activeP[3]); break;//playing game 
        case 14:
            howToPlay(); break;
        case 15:
            exit(0); break;
        default:
            break;
        }
        
    }
    

return 0;
}