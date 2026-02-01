#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

void gotoxy(int x, int y) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hConsole, pos);
#else
    printf("\033[%d;%dH", y, x);
#endif
}
