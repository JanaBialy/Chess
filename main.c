#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"
#include "undo.h"
int main()
{
    Board board;
    Move move;
    bool isnotempty_result = false;
    bool validinput_result = false;
    bool gameover = false;
    PieceColor winner = none;
    PieceColor currentcolor = white;
    printf("Welcome to Chess!\n");
    printf("===============================================\n");
    initboard(&board);
    while (!gameover)
    {
        fulldispboard(&board);
        printf("Current turn: %s\n", (currentcolor == white) ? "White" : "Black");
        do
        {
            move = takeinput(&board, currentcolor);
            isnotempty_result = isnotempty(&board, move);
            validinput_result = move.validinput && isnotempty_result;
        } while (!validinput_result);
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
        if(isincheck(&board, currentcolor))
        {
            printf("Check!\n");
        }
        if (ischeckmate(&board, currentcolor))
        {
            gameover = true;
            winner = (currentcolor == white) ? black : white;
            printf("Checkmate! \n%s wins!\n", (winner == white) ? "White" : "Black");
        }
        else if (isstalemate(&board, currentcolor))
        {
            gameover = true;
            winner = none;
            printf("Stalemate! The game is a draw.\n");
        }
        
    }
    
    return 0;
}