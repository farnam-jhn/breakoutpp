#include <iostream>
#include "getchar.h"


char optionChoosenByUser(){


    std::cout   << " -------Select option!-------" << std::endl
                << "       ╔══════════════╗      " << std::endl
                << "       ║ 1. New Game  ║      " << std::endl
                << "       ╚══════════════╝      " << std::endl << std::endl
                << "       ╔══════════════╗      " << std::endl
                << "       ║ 2.  Help     ║      " << std::endl
                << "       ╚══════════════╝      " << std::endl << std::endl
                << "       ╔══════════════╗      " << std::endl
                << "       ║ 3. History   ║      " << std::endl
                << "       ╚══════════════╝      " << std::endl << std::endl
                << "       ╔══════════════╗      " << std::endl
                << "       ║ 4.  Exit     ║      " << std::endl
                << "       ╚══════════════╝      " << std::endl;

    char chosenOpt = getch();
    return chosenOpt;
}
