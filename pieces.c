#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"

typedef struct
{
    int row;
    int col;
} move;

const move KNIGHT_MOVES[8] = {
    {2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};
const int KNIGHT_MOVES_COUNT = 8;

const move ROOK_MOVES[4] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int ROOK_MOVES_COUNT = 4;

const move BISHOP_MOVES[4] = {
    {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
const int BISHOP_MOVES_COUNT = 4;

const move QUEEN_MOVES[8] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const int QUEEN_MOVES_COUNT = 8;

const move KING_MOVES[8] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const int KING_MOVES_COUNT = 8;

const move WHITE_PAWN_MOVES[1] = {
    {-1, 0}};
const int WHITE_PAWN_MOVES_COUNT = 1;

const move WHITE_PAWN_MOVES_FIRSTMOVE[1] = {
    {-2, 0}};
const int WHITE_PAWN_MOVES_FIRSTMOVE_COUNT = 1;

const move BLACK_PAWN_MOVES[1] = {
    {1, 0}};
const int BLACK_QUEEN_MOVES_COUNT = 1;

const move BLACK_PAWN_MOVES_FIRSTMOVE[1] = {
    {-2, 0}};
const int BLACK_PAWN_MOVES_FIRSTMOVE_COUNT = 1;

const move WHITE_PAWNC[2] = {
    {-1, -1}, {-1, 1}};
const int WHITE_PAWNC_COUNT = 2;

const move BLACK_PAWNC[2] = {
    {1, -1}, {1, 1}};
const int BLACK_PAWN_CAPTURE_COUNT = 2;

int absolute(int x)
{
    return (x < 0) ? -x : x;
}

bool ispathclear(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    int rowstep = 0;
    int colstep = 0;
    if (torow > fromrow)
        rowstep = 1;
    else if (torow < fromrow)
        rowstep = -1;
    if (tocol > fromcol)
        colstep = 1;
    else if (tocol < fromcol)
        colstep = -1;

    int currentrow = fromrow + rowstep;
    int currentcol = fromcol + colstep;
    while (currentrow != torow || currentcol != tocol)
    {
        if (board->squares[currentrow][currentcol].type != empty)
        {
            return false;
        }
        currentrow += rowstep;
        currentcol += colstep;
    }
    return true;
}

bool isvalidrookmove(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    if (fromrow != torow && fromcol != tocol)
    {
        return false;
    }
    if (!ispathclear(board, fromrow, fromcol, torow, tocol))
    {
        return false;
    }
    Piece dest = board->squares[torow][tocol];
    Piece src = board->squares[fromrow][fromcol];
    if (dest.type != empty && dest.color == src.color)
    {
        return false;
    }
    return true;
}

bool isvalidknightmove(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    int rowdiff = absolute(torow - fromrow);
    int coldiff = absolute(tocol - fromcol);
    if (!((rowdiff == 2 && coldiff == 1) || (rowdiff == 1 && coldiff == 2)))
    {
        return false;
    }
    Piece dest = board->squares[torow][tocol];
    Piece src = board->squares[fromrow][fromcol];
    if (dest.type != empty && dest.color == src.color)
    {
        return false;
    }
    return true;
}

bool isvalidbishopmove(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    int rowdiff = absolute(torow - fromrow);
    int coldiff = absolute(tocol - fromcol);
    if (rowdiff != coldiff)
    {
        return false;
    }
    if (!ispathclear(board, fromrow, fromcol, torow, tocol))
    {
        return false;
    }
    Piece dest = board->squares[torow][tocol];
    Piece src = board->squares[fromrow][fromcol];
    if (dest.type != empty && dest.color == src.color)
    {
        return false;
    }
    return true;
}

bool isvalidqueenmove(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    if ((isvalidrookmove(board, fromrow, fromcol, torow, tocol)) || (isvalidbishopmove(board, fromrow, fromcol, torow, tocol)))
        return true;
    else
        return false;
    Piece dest = board->squares[torow][tocol];
    Piece src = board->squares[fromrow][fromcol];
    if (dest.type != empty && dest.color == src.color)
    {
        return false;
    }
    return true;
}
bool isvalidkingmove(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    int rowdiff = absolute(torow - fromrow);
    int coldiff = absolute(tocol - fromcol);
    if (rowdiff > 1 || coldiff > 1)
    {
        return false;
    }
    Piece dest = board->squares[torow][tocol];
    Piece src = board->squares[fromrow][fromcol];
    if (dest.type != empty && dest.color == src.color)
    {
        return false;
    }
    return true;
}

bool isvalidpawnmove(Board *board, int fromrow, int fromcol, int torow, int tocol)
{
    Piece pawn = board->squares[fromrow][fromcol];
    int rowdiff = torow - fromrow;
    int coldiff = absolute(tocol - fromcol);
    if (pawn.color == white)
    {
        if (coldiff == 0)
        {
            if (board->squares[torow][tocol].type != empty)
            {
                return false;
            }
            if (rowdiff == -1)
            {
                return true;
            }
            if (fromrow == 6 && rowdiff == -2)
            {
                if (!ispathclear(board, fromrow, fromcol, torow, tocol))
                {
                    return false;
                }
                return true;
            }
        }
        else if (coldiff == 1 && rowdiff == -1)
        {
            Piece destpiece = board->squares[torow][tocol];
            if (destpiece.type != empty && destpiece.color == black)
            {
                return true;
            }
            if (board->enpassantpossible && tocol == board->enpassantcol && torow == board->enpassantrow)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else if (pawn.color == black)
    {
        if (coldiff == 0)
        {
            if (board->squares[torow][tocol].type != empty)
            {
                return false;
            }
            if (rowdiff == 1)
            {
                return true;
            }
            if (fromrow == 1 && rowdiff == 2)
            {
                if (!ispathclear(board, fromrow, fromcol, torow, tocol))
                {
                    return false;
                }
                return true;
            }
        }
        else if (coldiff == 1 && rowdiff == 1)
        {
            Piece destpiece = board->squares[torow][tocol];
            if (destpiece.type != empty && destpiece.color == white)
            {
                return true;
            }
            if (board->enpassantpossible && tocol == board->enpassantcol && torow == board->enpassantrow)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

bool cancastle(Board *board, PieceColor color, bool kingside)
{
    int row = (color == white) ? 7 : 0;
    if (!kingside)
    {
        return cancastlequeenside(board, color);
    }
    Piece kingpiece = board->squares[row][4];
    Piece rookpiece = board->squares[row][7];
    if (rookpiece.type != rook || rookpiece.hasmoved || rookpiece.color != color)
    {
        printf("Cannot castle: Rook has moved or is not present!\n");
        return false;
    }
    if (kingpiece.type != king || kingpiece.hasmoved || kingpiece.color != color)
    {
        printf("Cannot castle: King has moved or is not present!\n");
        return false;
    }
    if (!ispathclear(board, row, 4, row, 7))
    {
        printf("Cannot castle: Path between king and rook is not clear!\n");
        return false;
    }
    if (isincheck(board, color))
    {
        printf("Cannot castle: King is in check!\n");
        return false;
    }
    if (issquareattacked(board, row, 5, (color == white) ? black : white) || issquareattacked(board, row, 6, (color == white) ? black : white))
    {
        printf("Cannot castle: Squares king passes through are under attack!\n");
        return false;
    }
    return true;
}

bool cancastlequeenside(Board *board, PieceColor color)
{
    int row = (color == white) ? 7 : 0;
    Piece kingpiece = board->squares[row][4];
    Piece rookpiece = board->squares[row][0];
    if (rookpiece.type != rook || rookpiece.hasmoved || rookpiece.color != color)
    {
        printf("Cannot castle: Rook has moved or is not present!\n");
        return false;
    }
    if (kingpiece.type != king || kingpiece.hasmoved || kingpiece.color != color)
    {
        printf("Cannot castle: King has moved or is not present!\n");
        return false;
    }
    if (!ispathclear(board, row, 4, row, 0))
    {
        printf("Cannot castle: Path between king and rook is not clear!\n");
        return false;
    }
    if (isincheck(board, color))
    {
        printf("Cannot castle: King is in check!\n");
        return false;
    }
    if (issquareattacked(board, row, 3, (color == white) ? black : white) || issquareattacked(board, row, 2, (color == white) ? black : white))
    {
        printf("Cannot castle: Squares king passes through are under attack!\n");
        return false;
    }
    return true;
}
