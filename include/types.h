#ifndef Types_H
#define Types_H
#include <stdbool.h>
typedef enum
{
    empty,
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king
} PieceType;

typedef enum
{
    none,
    white,
    black
} PieceColor;

typedef struct
{
    PieceType type;
    PieceColor color;
    bool hasmoved;
} Piece;

typedef struct
{
    Piece squares[8][8];
    PieceColor turn;
    int enpassantcol;
    int enpassantrow;
    bool enpassantpossible;
    Piece capturedwhitepieces[16];
    int capturedwhitecount;
    Piece capturedblackpieces[16];
    int capturedblackcount;
} Board;

typedef struct
{
    int fromrow;
    int fromcol;
    int torow;
    int tocol;
    char promotion;
    bool validinput;
} Move;

typedef struct
{
    Board boardstate;
    PieceColor currentturn;
    Move movemade;
} MoveEntry;

typedef struct
{
    MoveEntry moves[500];
    int historycount;
    int current;
} History;
#endif