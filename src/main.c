#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"
#include "undo.h"
#include "save.h"
#include "timer.h"

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
    printf("=====================================================\n");
    Gameclock clock = setuptimermenu();
    initboard(&board);
    savestate(&board,currentcolor , move , &history);
    while (!gameover)
    {
        fulldispboard(&board);
        displaytimer(&clock);
        printf("Current turn: %s\n", (currentcolor == white) ? "White" : "Black");
        do
        {
            startmove(&clock);
            move = takeinput(&board, currentcolor,&issave ,&isload, &isundo ,&isredo ,&isquit);
            if (issave || isload || isundo || isredo || isquit){
                break ;
            }
            if (move.validinput){
                isnotempty_result = isnotempty(&board, move);
                validinput_result = move.validinput && isnotempty_result;
            }
            else{
                validinput_result = false ;
            }
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
            printf("GOODBYE :) \n");
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
        if (!endmove(&clock, currentcolor))
        {
            gameover = true;
            continue;
        }
        makemove(&board, move, &currentcolor);
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
        printf("=====================================================\n");
        displaymaterialadvantage(&board);
        savestate(&board,currentcolor , move , &history);
        if (gameover == true)
        {
            printf("Do you want to (save,undo) : ");
            char lastcommand[20] ;
            char cleanedver[10] ;
            if (!fgets(lastcommand, sizeof(lastcommand), stdin)) {
                isquit = true;
                return 0;
            }
            lastcommand[strcspn(lastcommand, "\n")] = '\0';
            if (strlen(lastcommand) == sizeof(lastcommand) - 1) {
                int c;
            while ((c = getchar()) != '\n' && c != EOF);
    }
            int j = 0;
            for (int i = 0; lastcommand[i] != '\0' && lastcommand[i] != '\n'; i++)
            {
                if (!isspace( lastcommand[i]))
                    cleanedver[j++] = toupper(lastcommand[i]);
            }
            cleanedver[j] = '\0';
            if (cleanedver[0] == 'S')
            {
                savegame(&board,currentcolor);
            }
            else if (cleanedver[0] == 'U')
            {
                gameover=false ;
                undomove(&board,&currentcolor,&history);
                continue;
            }
        }
    }
    return 0;
}