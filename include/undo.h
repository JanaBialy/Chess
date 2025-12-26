#ifndef UNDO_H
#define UNDO_H
#include "types.h"

void inithistory(History *history);
void savestate(Board *board, PieceColor turn, Move move, History *history);
bool undomove(Board *board, PieceColor *turn, History *history);
bool redomove(Board *board, PieceColor *turn, History *history);

#endif