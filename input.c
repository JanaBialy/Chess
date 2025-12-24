#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"

bool isvaliddestination(const Board *board, int torow, int tocol, PieceColor color)
{
    Piece destpiece = board->squares[torow][tocol];
    if (destpiece.type != empty && destpiece.color == color)
    {
        return false;
    }
    return true;
}

Move takeinput(Board *board, PieceColor currentturn ,bool *issave ,bool *isload ,bool *isundo ,bool *isredo ,bool *isquit)
{
    Move move;
    move.validinput = false;
    move.promotion = '\0';

    char input[50];
    char cleaned[8];

    printf("Enter your move (e.g., E2E4) or command (S,L,U,R,Q): ");
    fgets(input, 50, stdin);
    int j = 0;
    for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++)
    {
        if (!isspace(input[i]))
            cleaned[j++] = toupper(input[i]);
    }
    cleaned[j] = '\0';
    int len = strlen(cleaned);
    if(len == 1)
    {
        char command = toupper(cleaned[0]);
        if(command == 'S')
        {
            *issave = true ;
            return move;
        }
        else if (command == 'L')
        {
            *isload = true ;
            return move ;
        }
        else if (command == 'U')
        {
            *isundo = true ;
            return move ;
        }
        else if (command == 'R')
        {
            *isredo = true ;
            return move ;
        }
        else if (command == 'Q')
        {
            *isquit = true ;
            return move ;
        }
    }

    if (len > 5 || len < 4)
    {
        printf("Invalid input length!\n");
        return move;
    }

    if (!isalpha(cleaned[0]) || !isdigit(cleaned[1]) || !isalpha(cleaned[2]) || !isdigit(cleaned[3]))
    {
        printf("Invalid format!\n");
        return move;
    }

    move.fromcol = cleaned[0] - 'A';
    move.tocol = cleaned[2] - 'A';
    move.fromrow = '8' - cleaned[1];
    move.torow = '8' - cleaned[3];

    if (move.fromcol < 0 || move.fromcol > 7 ||
        move.tocol < 0 || move.tocol > 7 ||
        move.fromrow < 0 || move.fromrow > 7 ||
        move.torow < 0 || move.torow > 7)
    {
        printf("Out of Range!\n");
        return move;
    }

    if (len == 5)
    {
        char promotion = cleaned[4];
        if (promotion != 'Q' && promotion != 'R' &&
            promotion != 'B' && promotion != 'N')
        {
            printf("Invalid Promotion piece !\n");
            return move;
        }
        move.promotion = promotion;
    }
    if (!isvaliddestination(board, move.torow, move.tocol, currentturn))
    {
        printf("Invalid destination: cannot capture own piece!\n");
        return move;
    }
    if (board->squares[move.fromrow][move.fromcol].color != currentturn)
    {
        printf("It's not your turn!\n");
        return move;
    }
    move.validinput = true;
    return move;
}

bool movevalidation(Board *board, Move move)
{
    Piece piece = board->squares[move.fromrow][move.fromcol];
    bool isvalidmove = false;
    switch (piece.type)
    {
    case pawn:
        isvalidmove = isvalidpawnmove(board, move.fromrow, move.fromcol, move.torow, move.tocol);
        if (!isvalidmove)
        {
            printf("Invalid pawn move!\n");
        }
        break;
    case rook:
        isvalidmove = isvalidrookmove(board, move.fromrow, move.fromcol, move.torow, move.tocol);
        if (!isvalidmove)
        {
            printf("Invalid rook move!\n");
        }
        break;
    case knight:
        isvalidmove = isvalidknightmove(board, move.fromrow, move.fromcol, move.torow, move.tocol);
        if (!isvalidmove)
        {
            printf("Invalid knight move!\n");
        }
        break;
    case bishop:
        isvalidmove = isvalidbishopmove(board, move.fromrow, move.fromcol, move.torow, move.tocol);
        if (!isvalidmove)
        {
            printf("Invalid bishop move!\n");
        }
        break;
    case queen:
        isvalidmove = isvalidqueenmove(board, move.fromrow, move.fromcol, move.torow, move.tocol);
        if (!isvalidmove)
        {
            printf("Invalid queen move!\n");
        }
        break;
    case king:
        isvalidmove = isvalidkingmove(board, move.fromrow, move.fromcol, move.torow, move.tocol);
        if (!isvalidmove && absolute(move.tocol - move.fromcol) == 2 && move.fromrow == move.torow)
        {
            bool kingside = (move.tocol - move.fromcol) == 2;
            isvalidmove = cancastle(board, piece.color, kingside);
        }
        if (!isvalidmove)
        {
            printf("Invalid king move!\n");
        }
        break;
    default:
        printf("Invalid piece type!\n");
        isvalidmove = false;
    }
    return isvalidmove;
}

bool isnotempty(Board *board, Move move)
{
    if (board->squares[move.fromrow][move.fromcol].type == empty)
    {
        printf("This square is empty!\n");
        return false;
    }
    return true;
}
