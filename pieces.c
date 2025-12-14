#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"input.h"
#include"board.h"
#include"pieces.h"

int absolute(int x){
    return (x<0) ? -x : x ;
}

bool ispathclear(Board*board,int fromrow,int fromcol,int torow,int tocol){
    int rowstep = 0 ;
    int colstep = 0 ;
    if(torow>fromrow) 
        rowstep = 1 ;
    else if(torow<fromrow)
        rowstep = -1 ;
    if(tocol>fromcol)
        colstep = 1 ;
    else if(tocol<fromcol)
        colstep = -1 ;
    
    int currentrow = fromrow + rowstep ;
    int currentcol = fromcol + colstep ;
    while(currentrow != torow || currentcol != tocol){
        if(board->squares[currentrow][currentcol].type != empty){
            printf("Path not clear!\n");
            return false ;
        }
        currentrow += rowstep ;
        currentcol += colstep ;
    }
    return true ;
}

bool isvalidrookmove(Board*board,int fromrow,int fromcol, int torow,int tocol){
    if(fromrow!=torow && fromcol!=tocol){
        printf("Rook moves must be horizontal or vertical!\n");
        return false;
    }
    if(!ispathclear(board,fromrow,fromcol,torow,tocol)){
        printf("Rook's path is not clear!\n");
        return false;
    }
    return true;
}

bool isvalidknightmove(Board*board,int fromrow,int fromcol,int torow,int tocol){
    int rowdiff = absolute(torow - fromrow);
    int coldiff = absolute(tocol - fromcol);
    if(!((rowdiff==2 && coldiff==1)||(rowdiff==1 && coldiff==2))){
        printf("Invalid knight move(must be L shaped)!\n");
        return false;
    }
    return true;
}

bool isvalidbishopmove(Board*board,int fromrow,int fromcol,int torow,int tocol){
    int rowdiff = absolute(torow - fromrow);
    int coldiff = absolute(tocol - fromcol);
    if(rowdiff != coldiff){
        printf("Bishop moves must be diagonal!\n");
        return false;
    }
    if(!ispathclear(board,fromrow,fromcol,torow,tocol)){
        printf("Bishop's path is not clear!\n");
        return false;
    }
    return true;
}

bool isvalidqueenmove(Board*board,int fromrow,int fromcol,int torow,int tocol){
    if ((isvalidrookmove(board,fromrow,fromcol,torow,tocol))||(isvalidbishopmove(board,fromrow,fromcol,torow,tocol)))
        return true;
    else 
        return false;
    return true;
}
bool isvalidkingmove(Board*board,int fromrow,int fromcol,int torow,int tocol){
    int rowdiff = absolute(torow - fromrow);
    int coldiff = absolute(tocol - fromcol);
    if(rowdiff>1 || coldiff>1){
        printf("King moves only one square in any direction!\n");
        return false;
    }
    return true;
}

bool isvalidpawnmove(Board*board,int fromrow,int fromcol,int torow,int tocol){
    Piece pawn = board->squares[fromrow][fromcol];
    int rowdiff = torow - fromrow ;
    int coldiff = absolute(tocol - fromcol);
    if(pawn.color == white){
        if(coldiff == 0){
            if(rowdiff == -1){
                return true;
            }
            if(fromrow == 6 && rowdiff == -2){
                if(!ispathclear(board,fromrow,fromcol,torow,tocol)){
                    printf("Pawn's path is not clear!\n");
                    return false;
                }
                return true;
            }
        }
        else if(coldiff == 1 && rowdiff == -1){
            Piece destpiece = board->squares[torow][tocol];
            if(destpiece.type != empty && destpiece.color == black){
                return true;
            }
            else{
                printf("Invalid pawn capture move!\n");
                return false;
            }
        }
    }
    else if(pawn.color == black){
        if(coldiff == 0){
            if(rowdiff == 1){
                return true;
            }
            if(fromrow == 1 && rowdiff == 2){
                if(!ispathclear(board,fromrow,fromcol,torow,tocol)){
                    printf("Pawn's path is not clear!\n");
                    return false;
                }
                return true;
            }
        }
        else if(coldiff == 1 && rowdiff == 1){
            Piece destpiece = board->squares[torow][tocol];
            if(destpiece.type != empty && destpiece.color == white){
                return true;
            }
            else{
                printf("Invalid pawn capture move!\n");
                return false;
            }
        }
    }
    printf("Invalid pawn move!\n");
    return false;
}

