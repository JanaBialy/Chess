#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"input.h"
#include"board.h"
#include"pieces.h"
int main(){
    Board board;
    Move move;
    bool isnotempty_result = false;
    bool validinput_result = false;
    PieceColor currentcolor = white;
    initboard(&board);
    dispboard(&board);
    while(!validinput_result || !isnotempty_result){
        Move move = takeinput();
        isnotempty_result = isnotempty( move , &board);
        validinput_result = move.validinput;
    }
    return 0;
}