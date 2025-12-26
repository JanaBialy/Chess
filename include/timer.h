#ifndef TIMER_H
#define TIMER_H
#include "types.h"
#include <time.h>
#include <stdbool.h>

void initclock(Gameclock *clk, double minutes);
void startmove(Gameclock *clk);
bool endmove(Gameclock *clk, PieceColor color);
void displaytimer(Gameclock *clk);

Gameclock setuptimermenu(void);

#endif