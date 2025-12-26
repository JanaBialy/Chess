#ifndef SAVE_H
#define SAVE_H
#include "types.h"

void savegame(Board *board, PieceColor currentturn);
int loadgame(Board *board, PieceColor *currentturn);
#endif