#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"
#include "undo.h"
#include "save.h"

int main()
{
    Board board;
    Move move;
    bool issave = false ;
    bool isload = false ;
    bool isundo = false ;
    bool isredo = false ;
    bool isquit = false ;
    bool isnotempty_result = false;
    bool validinput_result = false;
    bool gameover = false;
    PieceColor winner = none;
    PieceColor currentcolor = white;
    History history;
    inithistory(&history);
    printf("Welcome to Chess!\n");
    printf("===============================================\n");
    initboard(&board);
    savestate(&board,currentcolor , move , &history);
    while (!gameover)
    {
        fulldispboard(&board);
        printf("Current turn: %s\n", (currentcolor == white) ? "White" : "Black");
        do
        {
            move = takeinput(&board, currentcolor,&issave ,&isload, &isundo ,&isredo ,&isquit);
            if (issave || isload || isundo || isredo || isquit){
                break ;
            }
            isnotempty_result = isnotempty(&board, move);
            validinput_result = move.validinput && isnotempty_result;
        } while (!validinput_result);
        if(issave)
        {
            savegame(&board,currentcolor);
            issave = false ;
            continue;
        }
        else if(isload)
        {
            loadgame(&board,&currentcolor);
            isload = false ;
            continue;
        }
        else if(isundo)
        {
            undomove(&board,&currentcolor , &history);
            isundo = false ;
            continue;
        }  
        else if(isredo)
        {
            redomove(&board,&currentcolor , &history);
            isredo = false ;
            continue;
        }
        else if(isquit)
        {
            printf("GOODBYE :) ");
            isquit = false ;
            return 0;
        }
        isundo = isredo = isload = issave = isquit = false ;
        bool isvalidmove = movevalidation(&board, move);
        if (isvalidmove && wouldbeincheck(&board, move, currentcolor))
        {
            printf("Invalid move: King would be in check!\n");
            isvalidmove = false;
        }
        if (!isvalidmove)
        {
            printf("Invalid move!\n");
            continue;
        }
        makemove(&board, move, &currentcolor);
        displaymaterialadvantage(&board);
        if (isincheck(&board, currentcolor))
        {
            printf("Check!\n");
        }
        if (ischeckmate(&board, currentcolor))
        {
            gameover = true;
            winner = (currentcolor == white) ? black : white;
            printf("CHECKMATE! %s WINS!\n", (winner == white) ? "White" : "Black");
        }
        else if (isstalemate(&board, currentcolor))
        {
            gameover = true;
            winner = none;
            printf("Stalemate! The game is a draw.\n");
        }
        savestate(&board,currentcolor , move , &history);
    }
    return 0;
}