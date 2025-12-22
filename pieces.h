#ifndef PIECES_H
#define PIECES_H
#include "types.h"

bool isvalidrookmove(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool isvalidknightmove(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool isvalidbishopmove(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool isvalidqueenmove(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool isvalidkingmove(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool isvalidpawnmove(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool ispathclear(Board *board, int fromrow, int fromcol, int torow, int tocol);
bool cancastle(Board *board, PieceColor color, bool kingside);
bool cancastlequeenside(Board *board, PieceColor color);
int absolute(int x);

#endif
