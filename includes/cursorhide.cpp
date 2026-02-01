#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

void show_console_cursor(bool show) {
#if defined(_WIN32)
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(handle, &cci);
    cci.bVisible = show;
    SetConsoleCursorInfo(handle, &cci);
#else
    std::cout << (show ? "\033[?25h" : "\033[?25l");
#endif
}
