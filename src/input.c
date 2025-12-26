#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "board.h"
#include "pieces.h"
#include "types.h"

void clearinputbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

bool isvaliddestination(const Board *board, int torow, int tocol, PieceColor color)
{
    Piece destpiece = board->squares[torow][tocol];
    if (destpiece.type != empty && destpiece.color == color)
    {
        return false;
    }
    return true;
}

Move takeinput(Board *board, PieceColor currentturn, bool *issave, bool *isload, bool *isundo, bool *isredo, bool *isquit)
{
    Move move;
    move.validinput = false;
    move.promotion = '\0';

    char input[50];
    char cleaned[8];

    printf("Enter your move (e.g., E2E4) or command (S,L,U,R,Q): ");
    if (!fgets(input, sizeof(input), stdin))
    {
        *isquit = true;
        return move;
    }
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) == sizeof(input) - 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    int j = 0;
    for (int i = 0; input[i] != '\0' && input[i] != '\n' && i < 50 && j < 7; i++)
    {
        if (!isspace(input[i]))
            cleaned[j++] = toupper(input[i]);
    }
    cleaned[j] = '\0';
    int len = strlen(cleaned);
    if (len == 1)
    {
        char command = toupper(cleaned[0]);
        if (command == 'S')
        {
            *issave = true;
            return move;
        }
        else if (command == 'L')
        {
            *isload = true;
            return move;
        }
        else if (command == 'U')
        {
            *isundo = true;
            return move;
        }
        else if (command == 'R')
        {
            *isredo = true;
            return move;
        }
        else if (command == 'Q')
        {
            *isquit = true;
            return move;
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
        printf("Invalid destination!\n");
        return move;
    }
    if (board->squares[move.fromrow][move.fromcol].color != currentturn && board->squares[move.fromrow][move.fromcol].type != empty)
    {
        printf("It's not your turn!\n");
        return move;
    }
    if (len == 4)
    {
        Piece piece = board->squares[move.fromrow][move.fromcol];
        if (piece.type == pawn && move.torow == (piece.color == white ? 0 : 7))
        {
            while (move.promotion == '\0')
            {
                printf("Please choose a promotion piece (Q, R, B, N):");
                char promo[10];
                if (!fgets(promo, sizeof(promo), stdin))
                {
                    *isquit = true;
                    return move;
                }
                promo[strcspn(promo, "\n")] = '\0';
                if (strlen(promo) == sizeof(promo) - 1)
                {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                }
                int k = 0;
                char cleanedpromo[10];
                for (int i = 0; promo[i] != '\0' && promo[i] != '\n'; i++)
                {
                    if (!isspace(promo[i]))
                        cleanedpromo[k++] = toupper(promo[i]);
                }
                cleanedpromo[k] = '\0';
                int lenpromo = strlen(cleanedpromo);
                if (lenpromo != 1)
                {
                    printf("Invalid promotion input length!\n");
                    continue;
                }
                move.promotion = toupper(cleanedpromo[0]);
                if (move.promotion != 'Q' && move.promotion != 'R' &&
                    move.promotion != 'B' && move.promotion != 'N')
                {
                    printf("Invalid Promotion piece !\n");
                    move.promotion = '\0';
                }
            }
        }
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
    if (board->squares[move.fromrow][move.fromcol].type == empty && move.validinput)
    {
        printf("This square is empty!\n");
        return false;
    }
    return true;
}
