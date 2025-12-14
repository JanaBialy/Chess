#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "board.h"
#include "input.h"
#include "pieces.h"

void initboard(Board *board){
    for(int row=0 ; row<BOARD_SIZE ; row++){
        for(int col=0 ; col<BOARD_SIZE ; col++){
            board->squares[row][col].type = empty;
            board->squares[row][col].color = none;
        }
    }
    board->squares[7][0].type=rook;
    board->squares[7][0].color=white;

    board->squares[7][1].type=knight;
    board->squares[7][1].color=white;
    
    board->squares[7][2].type=bishop;
    board->squares[7][2].color=white;

    board->squares[7][3].type=queen;
    board->squares[7][3].color=white;
    
    board->squares[7][4].type=king;
    board->squares[7][4].color=white;
    
    board->squares[7][5].type=bishop;
    board->squares[7][5].color=white;
    
    board->squares[7][6].type=knight;
    board->squares[7][6].color=white;
    
    board->squares[7][7].type=rook;
    board->squares[7][7].color=white;

    for (int i =0; i<8; i++){
        board->squares[6][i].type=pawn;
        board->squares[6][i].color=white;

        board->squares[1][i].type=pawn;
        board->squares[1][i].color=black;
    }
    board->squares[0][0].type=rook;
    board->squares[0][0].color=black;

    board->squares[0][1].type=knight;
    board->squares[0][1].color=black;

    board->squares[0][2].type=bishop;
    board->squares[0][2].color=black;

    board->squares[0][3].type=queen;
    board->squares[0][3].color=black;

    board->squares[0][4].type=king;
    board->squares[0][4].color=black;

    board->squares[0][5].type=bishop;
    board->squares[0][5].color=black;

    board->squares[0][6].type=knight;
    board->squares[0][6].color=black;

    board->squares[0][7].type=rook;
    board->squares[0][7].color=black;

}

void dispboard(Board*board){
    printf("     A     B     C     D     E     F     G     H\n");
    printf("  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐\n");
    for(int row=0 ; row<BOARD_SIZE ; row++){
        printf("%d | ",8-row);
        for(int col=0 ; col<BOARD_SIZE ; col++){
            Piece p= board->squares[row][col];
            char piece =' ';
            if (p.type == empty){
                if((row+col)%2==0)
                printf(" ▓  | ");
                if ((row+col)%2)
                printf("    | ");
                continue;
            }
            else {
                switch (p.type){
                    case pawn:
                        piece = 'p';
                        break;
                    case rook:
                        piece = 'r';
                        break;
                    case knight:
                        piece = 'n';
                        break;
                    case bishop:
                        piece = 'b';
                        break;
                    case queen:
                        piece = 'q';
                        break;
                    case king:
                        piece = 'k';
                }
            if (p.color == black)
            piece-=32;   
            }
            printf(" %c  | ",piece);
        }
        printf(" %d\n",8-row);
        if (row < BOARD_SIZE -1){
            printf("  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤\n");
        }
    }
    printf("  └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘\n");
    printf("    A      B     C     D     E     F     G    H\n");
}

Piece getPiece(Board*board, int row , int col){
    return board->squares[row][col];
}

void setPiece(Board*board, int row , int col , Piece piece){
    board->squares[row][col] = piece ;
}

void makemove(Board*board,Move move){
    Piece piece = board->squares[move.fromrow][move.fromcol];
    if (move.promotion !='\0'){
        if (move.promotion == 'Q') piece.type = queen ;
        else if (move.promotion == 'R') piece.type = rook ;
        else if (move.promotion == 'B') piece.type = bishop ;
        else if (move.promotion == 'N') piece.type = knight ;
    }
    board->squares[move.torow][move.tocol]=piece ;
    board->squares[move.fromrow][move.fromcol].type=empty ;
    board->squares[move.fromrow][move.fromcol].color=none ;
}

Piece getcapturedpiece(Board*board,Move move){
    return board->squares[move.torow][move.tocol];
}

int issquareattacked(Board*board,int fromrow,int fromcol,PieceColor attackingcolor){
    for (int row=0 ; row<BOARD_SIZE ; row++){
        for (int col=0 ; col<BOARD_SIZE ; col++){
            Piece piece = board->squares[row][col];
            if (piece.color == attackingcolor){
                bool validmove = false ;
                switch (piece.type){
                    case pawn:
                        validmove = isvalidpawnmove(board,row,col,fromrow,fromcol);
                        break;
                    case rook:
                        validmove = isvalidrookmove(board,row,col,fromrow,fromcol);
                        break;
                    case knight:
                        validmove = isvalidknightmove(board,row,col,fromrow,fromcol);
                        break;
                    case bishop:
                        validmove = isvalidbishopmove(board,row,col,fromrow,fromcol);
                        break;
                    case queen:
                        validmove = isvalidqueenmove(board,row,col,fromrow,fromcol);
                        break;
                    case king:
                        validmove = isvalidkingmove(board,row,col,fromrow,fromcol);
                        break;
                    default:
                        break;
                }
                if (validmove){
                    return 1 ;
                }}}}
    return 0 ;
}

void findKing(Board*board, PieceColor color, int* kingRow, int* kingCol){
    for(int row=0 ; row<BOARD_SIZE ; row++){
        for(int col=0 ; col<BOARD_SIZE ; col++){
            Piece piece = board->squares[row][col];
            if(piece.type == king && piece.color == color){
                *kingRow = row ;
                *kingCol = col ;
                return ;
            }
        }
    }
    *kingRow = -1 ;
    *kingCol = -1 ;
}

int isincheck(Board*board,PieceColor color){
    int kingrow , kingcol ;
    findKing(board,color,&kingrow,&kingcol);
    if (kingrow == -1 || kingcol == -1){
        return 0 ;
    }
    PieceColor opponentcolor = (color == white) ? black : white ;
    return issquareattacked(board,kingrow,kingcol,opponentcolor);
}