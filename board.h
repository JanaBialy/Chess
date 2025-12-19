#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE 8

typedef enum{
    empty,
    pawn,
    rook,
    knight,
    bishop,
    queen,
    king
} PieceType;

typedef enum{
    none,
    white, 
    black
} PieceColor;

typedef struct{
    PieceType type ;
    PieceColor color ;
}Piece;

typedef struct {
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

void initboard(Board*board);
void dispboard(Board*board);
void displaycapturedpieces(Board*board);
void fulldispboard(Board*board);
Piece getPiece (Board*board, int row , int col);
void setPiece(Board*board, int row , int col , Piece piece);
void makemove(Board*board,Move move);
Piece getcapturedpiece(Board*board, Move move);
int issquareattacked(Board*board,int fromrow,int fromcol,PieceColor attackingcolor);
void findKing(Board*board, PieceColor color, int* kingRow, int* kingCol);
int isincheck(Board*board,PieceColor color);
int wouldbeincheck(Board*board, Move move, PieceColor color);
int hasvalidmoves(Board* board, PieceColor color);
int ischeckmate(Board* board,PieceColor color);
int isstalemate(Board* board,PieceColor color);
int getmaterialcount(Board* board, PieceColor color);
void displaymaterialadvantage(const Board*board);

extern Board board;

#endif