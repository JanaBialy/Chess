#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"

void inithistory(History *history)
{
    history->historycount = 0;
    history->current = -1;
}
void savestate(Board*board,PieceColor turn , Move move,History *history)
{
    if(history->historycount>=500)
    {
        for(int i=0 ; i<500-1 ; i++)
        {
            history->moves[i]=history->moves[i+1];
        }
        history->historycount--;
        history->current--;
        printf("Note: History limit reached . Oldest move removed.\n");
    }
    if (history->current < history->historycount-1)
    {
        history->historycount =  history->current+1;
    }
    history->current = history->historycount;
    MoveEntry *entry = &history->moves[history->current];
    entry->boardstate = *board;
    entry->currentturn = turn ;
    entry->movemade = move;
    history->historycount++;
    if(history->historycount>=500)
    {
        for(int i=0 ; i<500-1 ; i++)
        {
            history->moves[i]=history->moves[i+1];
        }
        history->historycount--;
        history->current--;
        printf("Note: History limit reached . Oldest move removed.\n");
    }
}
bool undomove(Board*board,PieceColor*turn,History *history)
{
    if(history->current<=0)
    {
        printf("No moves to undo\n");
        return false ;
    }
    history->current--;

    if(history->current < 0 || history->current >= history->historycount)
    {
        printf("ERROR: History index out of bounds!\n");
        history->current = 0; 
        return false;
    }

    MoveEntry *entry = &history->moves[history->current];
    *board = entry->boardstate;
    *turn = entry->currentturn;
    printf("Move undone.\n");
    printf("Moves in history: %d\n", history->current);
    return true;
}

bool redomove(Board*board,PieceColor *turn,History *history)
{
    if (history->current >= history->historycount-1)
    {
        printf("No moves to redo\n");
        return false;
    }
    history->current++;
    MoveEntry *entry = &history->moves[history->current];
    *board = entry->boardstate;
    *turn = entry->currentturn;
    printf("Move redone.\n");
    printf("Moves in history: %d\n", history->current);
    return true;
}

int canundo(History *history)
{
    return (history->current > 0);
}
int canredo(History *history)
{
    return (history->current < history->historycount-1);
}