#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "board.h"
#include "input.h"
#include "pieces.h"
#include "types.h"
#include "undo.h"

void initboard(Board *board)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            board->squares[row][col].type = empty;
            board->squares[row][col].color = none;
            board->squares[row][col].hasmoved = false;
        }
    }
    board->squares[7][0].type = rook;
    board->squares[7][0].color = white;

    board->squares[7][1].type = knight;
    board->squares[7][1].color = white;

    board->squares[7][2].type = bishop;
    board->squares[7][2].color = white;

    board->squares[7][3].type = queen;
    board->squares[7][3].color = white;

    board->squares[7][4].type = king;
    board->squares[7][4].color = white;

    board->squares[7][5].type = bishop;
    board->squares[7][5].color = white;

    board->squares[7][6].type = knight;
    board->squares[7][6].color = white;

    board->squares[7][7].type = rook;
    board->squares[7][7].color = white;

    for (int i = 0; i < 8; i++)
    {
        board->squares[6][i].type = pawn;
        board->squares[6][i].color = white;

        board->squares[1][i].type = pawn;
        board->squares[1][i].color = black;
    }
    board->squares[0][0].type = rook;
    board->squares[0][0].color = black;

    board->squares[0][1].type = knight;
    board->squares[0][1].color = black;

    board->squares[0][2].type = bishop;
    board->squares[0][2].color = black;

    board->squares[0][3].type = queen;
    board->squares[0][3].color = black;

    board->squares[0][4].type = king;
    board->squares[0][4].color = black;

    board->squares[0][5].type = bishop;
    board->squares[0][5].color = black;

    board->squares[0][6].type = knight;
    board->squares[0][6].color = black;

    board->squares[0][7].type = rook;
    board->squares[0][7].color = black;

    board->capturedwhitecount = 0;
    board->capturedblackcount = 0;
    for (int i = 0; i < 16; i++)
    {
        board->capturedwhitepieces[i].type = empty;
        board->capturedwhitepieces[i].color = none;
        board->capturedblackpieces[i].type = empty;
        board->capturedblackpieces[i].color = none;
    }
    board->enpassantpossible = false;
    board->enpassantcol = -1;
    board->enpassantrow = -1;
    board->turn = white;
}

void dispboard(Board *board)
{
    printf("     A     B     C     D     E     F     G     H\n");
    printf("  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐\n");
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        printf("%d | ", 8 - row);
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            Piece p = board->squares[row][col];
            if (p.type == empty)
            {
                if ((row + col) % 2 == 0)
                    printf("░░░░│ ");
                else
                    printf("    │ ");
                continue;
            }

            const char *piecesymbol = " ";
            switch (p.type)
            {
            case pawn:
                piecesymbol = (p.color == black) ? "♙" : "♟";
                break;
            case knight:
                piecesymbol = (p.color == black) ? "♘" : "♞";
                break;
            case bishop:
                piecesymbol = (p.color == black) ? "♗" : "♝";
                break;
            case rook:
                piecesymbol = (p.color == black) ? "♖" : "♜";
                break;
            case queen:
                piecesymbol = (p.color == black) ? "♕" : "♛";
                break;
            case king:
                piecesymbol = (p.color == black) ? "♔" : "♚";
                break;
            default:
                break;
            }

            printf(" %s  │ ", piecesymbol);
        }
        printf(" %d\n", 8 - row);
        if (row < BOARD_SIZE - 1)
        {
            printf("  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤\n");
        }
    }
    printf("  └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘\n");
    printf("    A      B     C     D     E     F     G    H\n");
}

Piece getPiece(Board *board, int row, int col)
{
    return board->squares[row][col];
}

void setPiece(Board *board, int row, int col, Piece piece)
{
    board->squares[row][col] = piece;
}

void makemove(Board *board, Move move, PieceColor *currentcolor)
{
    Piece piece = board->squares[move.fromrow][move.fromcol];
    if (piece.type == pawn && board->enpassantpossible)
    {
        if (piece.color == white && move.torow == board->enpassantrow && move.tocol == board->enpassantcol)
        {
            Piece capturedpawn = board->squares[move.torow + 1][move.tocol];
            board->capturedblackpieces[board->capturedblackcount++] = capturedpawn;
            board->squares[move.torow + 1][move.tocol].type = empty;
            board->squares[move.torow + 1][move.tocol].color = none;
            printf("En Passant capture!\n");
        }
        else if (piece.color == black && move.torow == board->enpassantrow && move.tocol == board->enpassantcol)
        {
            Piece capturedpawn = board->squares[move.torow - 1][move.tocol];
            board->capturedwhitepieces[board->capturedwhitecount++] = capturedpawn;
            board->squares[move.torow - 1][move.tocol].type = empty;
            board->squares[move.torow - 1][move.tocol].color = none;
            printf("En Passant capture!\n");
        }
    }
    board->enpassantpossible = false;
    board->enpassantcol = -1;
    board->enpassantrow = -1;
    if (piece.type == pawn)
    {
        if (piece.color == white && move.fromrow == 6 && move.torow == 4)
        {
            board->enpassantpossible = true;
            board->enpassantcol = move.tocol;
            board->enpassantrow = 5;
            printf("En Passant now available \n");
        }
        else if (piece.color == black && move.fromrow == 1 && move.torow == 3)
        {
            board->enpassantpossible = true;
            board->enpassantcol = move.tocol;
            board->enpassantrow = 2;
            printf("En Passant now available \n");
        }
    }
    Piece capturedpiece = board->squares[move.torow][move.tocol];
    if (capturedpiece.type != empty)
    {
        if (capturedpiece.color == white)
        {
            board->capturedwhitepieces[board->capturedwhitecount++] = capturedpiece;
        }
        else if (capturedpiece.color == black)
        {
            board->capturedblackpieces[board->capturedblackcount++] = capturedpiece;
        }
    }
    if (piece.type == pawn && move.promotion != '\0' && move.torow == (piece.color == white ? 0 : 7))
    {
        if (move.promotion == 'Q')
            piece.type = queen;
        else if (move.promotion == 'R')
            piece.type = rook;
        else if (move.promotion == 'B')
            piece.type = bishop;
        else if (move.promotion == 'N')
            piece.type = knight;
    }
    if (piece.type == king && absolute(move.tocol - move.fromcol) == 2)
    {
        bool kingside = (move.tocol - move.fromcol) == 2;
        bool iscastle = cancastle(board, piece.color, kingside);
        if (iscastle)
        {
            if (kingside)
            {
                board->squares[move.torow][move.tocol - 1] = board->squares[move.torow][7];
                board->squares[move.torow][move.tocol - 1].hasmoved = true;
                board->squares[move.torow][7].type = empty;
                board->squares[move.torow][7].color = none;
            }
            else
            {
                board->squares[move.torow][move.tocol + 1] = board->squares[move.torow][0];
                board->squares[move.torow][move.tocol + 1].hasmoved = true;
                board->squares[move.torow][0].type = empty;
                board->squares[move.torow][0].color = none;
            }
            printf("Castling performed!\n");
        }
    }
    board->squares[move.torow][move.tocol] = piece;
    board->squares[move.torow][move.tocol].hasmoved = true;
    board->squares[move.fromrow][move.fromcol].type = empty;
    board->squares[move.fromrow][move.fromcol].color = none;
    *currentcolor = (*currentcolor == white) ? black : white;
}

void displaycapturedpieces(Board *board)
{
    printf("Captured White Pieces: ");
    for (int i = 0; i < board->capturedwhitecount; i++)
    {
        Piece p = board->capturedwhitepieces[i];
        switch (p.type)
        {
        case pawn:
            printf("♟ ");
            break;
        case rook:
            printf("♜ ");
            break;
        case knight:
            printf("♞ ");
            break;
        case bishop:
            printf("♝ ");
            break;
        case queen:
            printf("♛ ");
            break;
        case king:
            printf("♚ ");
            break;
        case empty:
            continue;
        default:
            continue;
        }
    }
    printf("\nCaptured Black Pieces: ");
    for (int i = 0; i < board->capturedblackcount; i++)
    {
        Piece p = board->capturedblackpieces[i];
        switch (p.type)
        {
        case pawn:
            printf("♙ ");
            break;
        case rook:
            printf("♖ ");
            break;
        case knight:
            printf("♘ ");
            break;
        case bishop:
            printf("♗ ");
            break;
        case queen:
            printf("♕ ");
            break;
        case king:
            printf("♔ ");
            break;
        case empty:
            continue;
        default:
            continue;
        }
        
    }
    printf("\n");
}

void fulldispboard(Board *board)
{
    dispboard(board);
    displaycapturedpieces(board);
}

Piece getcapturedpiece(Board *board, Move move)
{
    return board->squares[move.torow][move.tocol];
}

int issquareattacked(Board *board, int fromrow, int fromcol, PieceColor attackingcolor)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            Piece piece = board->squares[row][col];
            if (piece.color == attackingcolor)
            {
                bool validmove = false;
                switch (piece.type)
                {
                case pawn:
                    validmove = isvalidpawnmove(board, row, col, fromrow, fromcol);
                    break;
                case rook:
                    validmove = isvalidrookmove(board, row, col, fromrow, fromcol);
                    break;
                case knight:
                    validmove = isvalidknightmove(board, row, col, fromrow, fromcol);
                    break;
                case bishop:
                    validmove = isvalidbishopmove(board, row, col, fromrow, fromcol);
                    break;
                case queen:
                    validmove = isvalidqueenmove(board, row, col, fromrow, fromcol);
                    break;
                case king:
                    validmove = isvalidkingmove(board, row, col, fromrow, fromcol);
                    break;
                default:
                    break;
                }
                if (validmove)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void findKing(Board *board, PieceColor color, int *kingRow, int *kingCol)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            Piece piece = board->squares[row][col];
            if (piece.type == king && piece.color == color)
            {
                *kingRow = row;
                *kingCol = col;
                return;
            }
        }
    }
    *kingRow = -1;
    *kingCol = -1;
}

int isincheck(Board *board, PieceColor color)
{
    int kingrow, kingcol;
    findKing(board, color, &kingrow, &kingcol);
    if (kingrow == -1 || kingcol == -1)
    {
        return 0;
    }
    PieceColor opponentcolor = (color == white) ? black : white;
    return issquareattacked(board, kingrow, kingcol, opponentcolor);
}

int wouldbeincheck(Board *board, Move move, PieceColor color)
{
    Piece from = board->squares[move.fromrow][move.fromcol];
    Piece to = board->squares[move.torow][move.tocol];

    board->squares[move.torow][move.tocol] = board->squares[move.fromrow][move.fromcol];
    board->squares[move.fromrow][move.fromcol].color = none;
    board->squares[move.fromrow][move.fromcol].type = empty;
    board->squares[move.fromrow][move.fromcol].hasmoved = false;

    int ischeck = isincheck(board, color);

    board->squares[move.fromrow][move.fromcol] = from;
    board->squares[move.torow][move.tocol] = to;
    return ischeck;
}

int hasvalidmoves(Board *board, PieceColor color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board->squares[i][j].type == empty)
                continue;
            if (board->squares[i][j].color != color)
                continue;
            for (int dr = 0; dr < 8; dr++)
            {
                for (int dc = 0; dc < 8; dc++)
                {
                    if (dr == i && dc == j)
                        continue;
                    Move move;
                    move.fromrow = i;
                    move.fromcol = j;
                    move.torow = dr;
                    move.tocol = dc;
                    bool validmove = false;

                    switch (board->squares[i][j].type)
                    {
                    case pawn:
                        validmove = isvalidpawnmove(board, i, j, dr, dc);
                        break;
                    case rook:
                        validmove = isvalidrookmove(board, i, j, dr, dc);
                        break;
                    case knight:
                        validmove = isvalidknightmove(board, i, j, dr, dc);
                        break;
                    case bishop:
                        validmove = isvalidbishopmove(board, i, j, dr, dc);
                        break;
                    case queen:
                        validmove = isvalidqueenmove(board, i, j, dr, dc);
                        break;
                    case king:
                        validmove = isvalidkingmove(board, i, j, dr, dc);
                        break;
                    default:
                        continue;
                    }
                    if (validmove)
                    {
                        if (!wouldbeincheck(board, move, color))
                            return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int ischeckmate(Board *board, PieceColor color)
{
    if (isincheck(board, color) && !hasvalidmoves(board, color))
        return 1;
    return 0;
}
int isstalemate(Board *board, PieceColor color)
{
    if (!isincheck(board, color) && !hasvalidmoves(board, color))
        return 1;
    return 0;
}

int getmaterialcount(PieceType type)
{
    switch (type)
    {
    case pawn:
        return 1;
    case knight:
        return 3;
    case bishop:
        return 3;
    case rook:
        return 5;
    case queen:
        return 9;
    case king:
        return 0;
    default:
        return 0;
    }
}

void displaymaterialadvantage(const Board *board)
{
    int whitecapturedvalues = 0;
    int blackcapturedvalues = 0;
    for (int i = 0; i < board->capturedwhitecount; i++)
    {
        whitecapturedvalues += getmaterialcount(board->capturedwhitepieces[i].type);
    }
    for (int i = 0; i < board->capturedblackcount; i++)
    {
        blackcapturedvalues += getmaterialcount(board->capturedblackpieces[i].type);
    }
    int materialdifference = blackcapturedvalues - whitecapturedvalues;
    if (materialdifference> 0)
    {
        printf("White has a material advantage of %d points.\n", materialdifference);
    }
    else if (materialdifference < 0)
    {
        printf("Black has a material advantage of %d points.\n", -materialdifference);
    }
    else
    {
        printf("Equal no advantage!\n");
    }
}
