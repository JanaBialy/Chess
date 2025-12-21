#ifndef INPUT_H
#define INPUT_H
#include "board.h"
#include "pieces.h"
#include <stdbool.h>

typedef struct
{
    int fromrow;
    int fromcol;
    int torow;
    int tocol;
    char promotion;
    bool validinput;
} Move;

Move takeinput(Board *board, PieceColor currentturn);
bool isvaliddestination(const Board *board, int torow, int tocol, PieceColor color);
bool isnotempty(Move move, Board *board);

#endif