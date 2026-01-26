#pragma once  // prevents multiple inclusion

#include <cstdlib>
#if defined(_WIN32) || defined(_WIN64)
inline void clear(){
    system("cls");
}
#else
inline void clear(){
    system("clear");
}
#endif
