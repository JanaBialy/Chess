#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include"input.h"
#include"board.c"

bool isvalidinput(int fromint, char fromchar, int toint, char tochar);
bool isnotempty(int fromint, char fromchar);
bool isfree(int toint, char tochar);

