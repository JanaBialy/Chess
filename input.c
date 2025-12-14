#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"input.h"
#include"board.h"
#include"pieces.h"

bool isvaliddestination(const Board *board, int torow, int tocol, PieceColor color){
    Piece destpiece = board->squares[torow][tocol];
    if (destpiece.type != empty && destpiece.color == color){
        return false;
    }
    return true;
}

Move takeinput(Board *board, PieceColor currentturn){
    Move move ;
    move.validinput=false;
    move.promotion='\0';

    char input[50];
    char cleaned[8];

    printf("Enter your move (e.g., E2E4): ");
    fgets(input, 50, stdin);
    int j=0;
    for(int i=0; input[i]!='\0' && input[i]!= '\n'; i++){
        if (!isspace(input[i]))
        cleaned[j++]= toupper(input[i]);
    }
    cleaned[j] = '\0';
    int len = strlen(cleaned);
    if (len> 5 || len<4){
        printf("Invalid input length!\n");
        return move;
    }

    if (!isalpha(cleaned[0]) || !isdigit(cleaned[1]) || !isalpha(cleaned[2]) || !isdigit(cleaned[3])){
        printf("Invalid format!\n");
        return move;
    }

    move.fromcol= cleaned[0] - 'A';
    move.tocol = cleaned[2] - 'A';
    move.fromrow = cleaned[1] - '1';
    move.torow = cleaned[3] - '1';

    if (move.fromcol <0 || move.fromcol>7 ||
        move.tocol<0 || move.tocol>7 ||
        move.fromrow<0 || move.fromrow>7 ||
        move.torow<0 || move.torow>7) {
        printf("Out of Range!\n");
        return move;
    }

    if (len == 5){
        char promotion = cleaned[4];
        if (promotion != 'Q' && promotion != 'R' &&
            promotion != 'B' && promotion != 'N'){
            printf("Invalid Promotion piece !\n");
            return move;
        }
        move.promotion = promotion;
    }
    if (!isvaliddestination(board, move.torow, move.tocol, currentturn)){
        printf("Invalid destination: cannot capture own piece!\n");
        return move;
    }
    move.validinput = true;
    return move;
}

bool isnotempty(Move move , Board *board){
    if (board->squares[move.fromrow][move.fromcol].type==empty){
        printf("This square is empty!\n");
        return false ;
    }
    return true;
}


