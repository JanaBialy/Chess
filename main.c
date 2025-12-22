#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"
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
        bool isvalidmove = false;
        Piece piece = board.squares[move.fromrow][move.fromcol];
        switch (piece.type)
        {
            case pawn:
                isvalidmove = isvalidpawnmove(&board, move.fromrow, move.fromcol, move.torow, move.tocol);
                break;
            case rook:
                isvalidmove = isvalidrookmove(&board, move.fromrow, move.fromcol, move.torow, move.tocol);
                break;
            case knight:
                isvalidmove = isvalidknightmove(&board, move.fromrow, move.fromcol, move.torow, move.tocol);
                break;
            case bishop:
                isvalidmove = isvalidbishopmove(&board, move.fromrow, move.fromcol, move.torow, move.tocol);
                break;
            case queen:
                isvalidmove = isvalidqueenmove(&board, move.fromrow, move.fromcol, move.torow, move.tocol);
                break;
            case king:
                isvalidmove = isvalidkingmove(&board, move.fromrow, move.fromcol, move.torow, move.tocol);
                if (!isvalidmove && absolute(move.tocol - move.fromcol) == 2 && move.fromrow == move.torow)
                {
                    bool kingside = (move.tocol - move.fromcol) == 2;
                    isvalidmove = cancastle(&board, currentcolor, kingside);
                }
                break;
            default:
                printf("Invalid piece type!\n");
                isvalidmove = false;
            }

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