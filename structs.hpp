#include <iostream>
#pragma once

struct color {
    const char* name;
    int r;
    int g;
    int b;
};
struct Snake {
    int nTail;
    int tailX[100];
    int tailY[100];
    int headX;
    int headY;
};
enum sDirection {
    STOP=0, UP, DOWN, RIGHT, LEFT
};
struct player {
    char name[20];
    color color;
    Snake snake;
    int score;
    sDirection dir;
    int win;
};
struct Fruit {
    int X;
    int Y;
};
struct Bomb {
    int X;
    int Y;
};
