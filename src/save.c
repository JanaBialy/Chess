#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "types.h"
#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif

void savesfolder(const char *foldername)
{
    struct stat st = {0};
    if (stat(foldername, &st) == -1)
    {
#ifdef _WIN32
        mkdir(foldername, 0);
#else
        mkdir(foldername, 0755);
#endif
        printf("Created a folder : %s\n", foldername);
    }
}

void savegame(Board *board, PieceColor currentturn)
{
    const char *foldername = "savedgames";
    savesfolder(foldername);
    char filename[100];
    printf("Enter filename to save (without extension): ");
    if (!fgets(filename, sizeof(filename), stdin))
    {
        printf("Error : cannot read filename\n");
        return;
    }
    filename[strcspn(filename, "\n")] = '\0';
    if (strlen(filename) == sizeof(filename) - 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    filename[strcspn(filename, "\n")] = 0;
    char fullname[200];
    snprintf(fullname, sizeof(fullname), "%s/%s.chess", foldername, filename);
    FILE *file = fopen(fullname, "wb");
    if (!file)
    {
        printf("Error : cannot create file '%s'\n", fullname);
        return;
    }
    fwrite(&currentturn, sizeof(PieceColor), 1, file);
    fwrite(board, sizeof(Board), 1, file);
    fclose(file);
    printf("✓ GAME SAVED TO '%s'\n", fullname);
}

int loadgame(Board *board, PieceColor *currentturn)
{
    const char *foldername = "savedgames";
    char filename[100];
    printf("Enter filename to load (without extension): ");
    if (!fgets(filename, sizeof(filename), stdin))
    {
        printf("Error : cannot read filename\n");
        return 0;
    }
    filename[strcspn(filename, "\n")] = '\0';
    if (strlen(filename) == sizeof(filename) - 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    char fullname[200];
    snprintf(fullname, sizeof(fullname), "%s/%s.chess", foldername, filename);
    FILE *file = fopen(fullname, "rb");
    if (!file)
    {
        printf("Error : cannot open file '%s'\n", fullname);
        return 0;
    }
    fread(currentturn, sizeof(PieceColor), 1, file);
    fread(board, sizeof(Board), 1, file);
    fclose(file);
    printf("✓ GAME LOADED FROM '%s'\n", fullname);
    return 1;
}