#ifndef PIECES_H
#define PIECES_H

struct move{
    int row ;
    int col ;
};

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
const int  QUEEN_MOVES_COUNT = 8 ;

const  move WHITE_PAWN_MOVES[1]={
    {-1,0}
};
const int  WHITE_QUEEN_MOVES_COUNT = 1 ;

const  move WHITE_PAWN_MOVES_FIRSTMOVE[1]={
    {-2,0}
};
const int  WHITE_QUEEN_MOVES__FIRSTMOVE_COUNT = 1 ;

const  move BLACK_PAWN_MOVES[1]={
    {-1,0}
};
const int  BLACK_QUEEN_MOVES_COUNT = 1 ;

const  move BLACK_PAWN_MOVES_FIRSTMOVE[1]={
    {-2,0}
};
const int  BLACK_QUEEN_MOVES__FIRSTMOVE_COUNT = 1 ;

const  move WHITE_PAWN_MOVES[1]={
    {-1,0}
};
const int  WHITE_QUEEN_MOVES_COUNT = 1 ;

#endif
