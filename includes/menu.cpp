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

void helpMenu(){
    system("clear");
    std::cout << std::endl << std::endl
              << "\033[34m    ╔══════════════════════════════════════════════════════════════════════╗      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  The game consist of few elements :                                  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  1. The ball, 2. Paddel, 3. Blocks                                   "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  The ball starts moving in a line; whenever the ball hits the wall,  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  a block or the paddel it reflects like a beam and whenever it hits  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  a block, the block gets destroyed.                                  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  The goal is to destroy all of the blocks                            "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  If your ball fall down and don't touch the paddel you lose a        "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  heart; you have 3 hearts, if you lose them all you lose.            "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  You can move the paddel using \"A\" & \"D\" to move left & right.       "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  Press \"P\" or \"p\" to pause the game.                                 "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "  Press any button to exit.                                           "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m    ╚══════════════════════════════════════════════════════════════════════╝      \033[0m" << std::endl;

    getch();
}
