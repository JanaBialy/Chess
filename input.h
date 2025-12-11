#ifndef INPUT_H
#define INPUT_H
#include"board.h"
#include<stdbool.h>

typedef struct{
    int fromrow;
    int fromcol;
    int torow;
    int tocol;
    char promotion;
    bool validinput;
} Move;



Move takeinput();

bool isnotempty(Move move , Board *board);

#endif