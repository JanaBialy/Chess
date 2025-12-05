#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE 8

typedef struct{
    char type ;
    char color ;
}Piece;

void initboard();
void basicboard();
Piece getPiece (int row , int col);
void setPiece(int row , int col , Piece piece);

#endif