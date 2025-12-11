#ifndef PIECES_H
#define PIECES_H
#include"board.h"

typedef struct{
    int row ;
    int col ;
}move;

const move KNIGHT_MOVES[8]={
    {2,1},{2,-1},{1,2},{1,-2},{-2,1},{-2,-1},{-1,2},{-1,-2}
};
const int  KNIGHT_MOVES_COUNT = 8 ;

const move ROOK_MOVES[4]={
    {1,0},{-1,0},{0,1},{0,-1}
};
const int ROOK_MOVES_COUNT = 4 ;

const move BISHOP_MOVES[4]={
    {1,1},{-1,-1},{1,-1},{-1,1}
};
const int BISHOP_MOVES_COUNT = 4 ;

const move QUEEN_MOVES[8]={
    {1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}
};
const int  QUEEN_MOVES_COUNT = 8 ;

const move KING_MOVES[8]={
    {1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}
};
const int  KING_MOVES_COUNT = 8 ;

const  move WHITE_PAWN_MOVES[1]={
    {-1,0}
};
const int  WHITE_PAWN_MOVES_COUNT = 1 ;

const  move WHITE_PAWN_MOVES_FIRSTMOVE[1]={
    {-2,0}
};
const int  WHITE_PAWN_MOVES_FIRSTMOVE_COUNT = 1 ;

const  move BLACK_PAWN_MOVES[1]={
    {1,0}
};
const int  BLACK_QUEEN_MOVES_COUNT = 1 ;

const  move BLACK_PAWN_MOVES_FIRSTMOVE[1]={
    {-2,0}
};
const int  BLACK_PAWN_MOVES_FIRSTMOVE_COUNT = 1 ;


const move WHITE_PAWNC[2] = {
    {-1, -1}, {-1, 1}
};
const int WHITE_PAWNC_COUNT = 2;

const move BLACK_PAWNC[2] = {
    {1, -1}, {1, 1}
};
const int BLACK_PAWN_CAPTURE_COUNT = 2;

typedef enum {
    WHITE , BLACK 
}color;

typedef enum {
    EMPTY , PAWN , KNIGHT , BISHOP , ROOK , QUEEN , KING
}piece_type;


bool isvaliddestination(const Board *board, int torow, int tocol, PieceColor color);
bool isvalidrookmove(Board*board,int fromrow, int fromcol, int torow, int tocol);
bool isvalidknightmove(Board*board,int fromrow, int fromcol, int torow, int tocol);
bool isvalidbishopmove(Board*board,int fromrow, int fromcol, int torow, int tocol);
bool isvalidqueenmove(Board*board,int fromrow, int fromcol, int torow, int tocol);
bool isvalidkingmove(Board*board,int fromrow, int fromcol, int torow, int tocol);
bool isvalidpawnmove(Board*board,int fromrow, int fromcol, int torow, int tocol);

#endif
