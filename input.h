#ifndef INPUT_H
#define INPUT_H
void takeinput(char fromchar, int fromint, char tochar, int toint);
bool isvalidinput(char fromchar, int fromint, char tochar, int toint);
bool isnotempty(char fromchar, int fromint );
bool isfree(char tochar, int toint);
#endif