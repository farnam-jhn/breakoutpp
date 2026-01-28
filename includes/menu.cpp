#include <iostream>
#include "getchar.h"




char optionChoosenByUser(){


    std::cout   << "\n\n\033[33m    <-------Select option!------->\033[0m" << std::endl
                << "\033[34m           ╔══════════════╗      \033[0m" << std::endl
                << "\033[34m           ║\033[0m"
                <<" 1. New Game  "
                <<"\033[34m║      \033[0m" << std::endl
                << "\033[34m           ╚══════════════╝      \033[0m" << std::endl << std::endl
                << "\033[34m           ╔══════════════╗      \033[0m" << std::endl
                << "\033[34m           ║\033[0m"
                <<" 2.   Help    "
                <<"\033[34m║      \033[0m" << std::endl
                << "\033[34m           ╚══════════════╝      \033[0m" << std::endl << std::endl
                << "\033[34m           ╔══════════════╗      \033[0m" << std::endl
                << "\033[34m           ║\033[0m"
                <<" 3.  History  "
                <<"\033[34m║      \033[0m" << std::endl
                << "\033[34m           ╚══════════════╝      \033[0m" << std::endl << std::endl
                << "\033[34m           ╔══════════════╗      \033[0m" << std::endl
                << "\033[34m           ║\033[0m"
                <<" 4.   Exit    "
                <<"\033[34m║      \033[0m" << std::endl
                << "\033[34m           ╚══════════════╝      \033[0m" << std::endl;

    char chosenOpt = getch();
    return chosenOpt;
}
