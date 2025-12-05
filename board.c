#include <stdio.h>
#include "board.h"

Piece board[BOARD_SIZE][BOARD_SIZE];

void initboard(){
    for(int row=0 ; row<BOARD_SIZE ; row++){
        for(int col=0 ; col<BOARD_SIZE ; col++){
            board[row][col].type = ' ';
            board[row][col].color = ' ';
        }
    }
}

void basicboard(){
    printf("    A   B   C   D   E   F   G   H\n");
    printf("  +-------------------------------+\n");
    for(int row=0 ; row<BOARD_SIZE ; row++){
        printf("%d | ",8-row);
        for(int col=0 ; col<BOARD_SIZE ; col++){
            printf("%c | ",board[row][col]);
        }
        printf(" %d\n",8-row);
    }
    printf("  +-------------------------------+\n");
    printf("    A   B   C   D   E   F   G   H\n");
}

Piece getPiece(int row , int col){
    return board[row][col];
}

void setPiece(int row , int col , Piece piece){
    board[row][col] = piece ;
}

int main(){
    initboard();
    basicboard();
}