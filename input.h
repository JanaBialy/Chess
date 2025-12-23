#ifndef INPUT_H
#define INPUT_H
#include "types.h"
#include <stdbool.h>

Move takeinput(Board *board, PieceColor currentturn ,bool *issave ,bool *isload ,bool *isundo ,bool *isredo ,bool *isquit);
bool isvaliddestination(const Board *board, int torow, int tocol, PieceColor color);
bool isnotempty(Board *board, Move move);
bool movevalidation(Board *board, Move move);

#endif