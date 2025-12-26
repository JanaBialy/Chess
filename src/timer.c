#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "types.h" 
#include "timer.h"
#include "input.h"

void initclock(Gameclock *clk, double minutes)
{
    clk->whitetime = minutes * 60.0;
    clk->blacktime = minutes * 60.0;
    clk->enabled = true;
    clk->movestart = 0;
}

void startmove(Gameclock *clk)
{
    if (!clk->enabled)
        return;
    clk->movestart = clock();
}

bool endmove(Gameclock *clk, PieceColor color)
{
    if (!clk->enabled)
    return true;

    clock_t now = clock();
    double elapsed = ((double)(now - clk->movestart)) / CLOCKS_PER_SEC;

    if (color == white)
    {
        clk->whitetime -= elapsed;
        if (clk->whitetime <= 0.0)
        {
            printf("\n WHITE RAN OUT OF TIME! BLACK WINS!\n");
            return false;
        }
    }
    else {
        clk->blacktime -= elapsed;
        if (clk->blacktime <= 0.0)
        {
            printf("\n BLACK RAN OUT OF TIME! WHITE WINS!\n");
            return false;
        }
    }
    return true;
}

void displaytimer(Gameclock *clk)
{
    if (!clk->enabled)
        return;
    int whiteminutes = (int)(clk->whitetime) / 60;
    int whiteseconds = (int)(clk->whitetime) % 60;
    int blackminutes = (int)(clk->blacktime) / 60;
    int blackseconds = (int)(clk->blacktime) % 60;

    printf("Time - White: %02d:%02d | Black: %02d:%02d\n", whiteminutes, whiteseconds, blackminutes, blackseconds);
}
Gameclock setuptimermenu(void)
{
    Gameclock clk;
    clk.enabled = false;
    char input[20];
    char choice='\0';
    while (choice != 'Y' && choice != 'N')
    {
        printf("Please enter Y or N to enable timer: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Timer disabled (no input).\n");
            clk.enabled = false;
            return clk;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == sizeof(input) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        for (int i = 0; input[i] != '\0' && input[i] != '\n'&& i<20; i++)
        {
            if (!isspace(input[i]))
            {
                choice = toupper(input[i]);
                break;
            }
        }
    }

    if (choice == 'Y')
    {
        clk.enabled = true;
        printf("Enter the time in minutes: ");
        double minutes=0.0;
        while(minutes <= 0.0)
        {
            scanf("%lf", &minutes);
            clearinputbuffer();
            if (minutes <= 0.0)
            {
                printf("Please enter a positive number for minutes: ");
            }
        }
        initclock(&clk, minutes);
        printf("Timer set to %.2f minutes per player.\n", minutes);
    }
    else
    {
        printf("Timer disabled.\n");
    }
    return clk;
}