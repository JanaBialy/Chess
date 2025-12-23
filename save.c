#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

void savegame(Board*board , PieceColor currentturn)
{
    char filename[100];
    printf("Enter filename to save (without extension): ");
    fgets(filename,100,stdin);
    filename[strcspn(filename, "\n")]=0;
    char fullname[150];
    snprintf(fullname, sizeof(fullname),"%s.chess",filename);
    FILE *file = fopen(fullname,"wb");
    if(!file)
    {
        printf("Error : cannot create file '%s'\n",fullname);
        return  ;
    }
    fwrite(currentturn , sizeof(PieceColor) , 1 , file);
    fwrite(board , sizeof(Board) , 1 , file);
    fclose(file);
    printf("GAME SAVED TO '%s'\n",fullname);
}
int loadgame(Board*board , PieceColor *currentturn)
{
    char filename[100];
    printf("Enter filename to load (without extension): ");
    fgets(filename,100,stdin);
    filename[strcspn(filename, "\n")]=0;
    char fullname[150];
    snprintf(fullname, sizeof(fullname),"%s.chess",filename);
    FILE *file = fopen(fullname,"rb");
    if(!file)
    {
        printf("Error : cannot open file '%s'\n",fullname);
        return 0 ;
    }
    fread(currentturn , sizeof(PieceColor) , 1 , file);
    fread(board , sizeof(Board) , 1 , file);
    fclose(file);
    printf("GAME LOADED FROM '%s'\n",fullname);
    return 1;
}