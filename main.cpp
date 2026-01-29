// Headers

#include "includes/menu.h"
#include "includes/getchar.h"
#include "includes/clear.h"
#include <string>

// Structures

struct Palyer{
    int score;
    std::string name;
};

struct Location{
    int x;
    int y;
};

// Global variables



// Functions prototype

void ballLocationFunction(Location loc, double slope, double hDistance);
void helpMenu();

// Main function

int main(){

    // Menu

    while (true) {
        clear();
        char opt = optionChoosenByUser();
        switch (opt) {
            case '1':
            // TODO
            break;
            case '2':
                helpMenu();
            break;
            case '3':
            // TODO
            break;
            case '4':
                clear();
                std::cout << "Press \"c\" to confirm\n";
                char confirmChar = getch();
                if (confirmChar == 'c'){
                    clear();
                    return 0;
                }
                clear();
            break;

        }
    }

}

// Functions

void ballLocationFunction(Location loc, double slope, double hDistance){

    // y = ax + b

    loc.y = (double)loc.x * slope + hDistance;

}

void helpMenu(){
    clear();
    std::cout << std::endl << std::endl
              << "\033[34m           ╔══════════════════════════════════════════════════════════════════════╗      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  The game consist of few elements :                                  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  1. The ball, 2. Paddel, 3. Blocks                                   "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  The ball starts moving in a line; whenever the ball hits the wall,  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  a block or the paddel it reflects like a beam and whenever it hits  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  a block, the block gets destroyed.                                  "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  The goal is to destroy all of the blocks                            "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  If your ball fall down and don't touch the paddel you lose a        "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  heart; you have 3 hearts, if you lose them all you lose.            "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  You can move the paddel using \"A\" & \"D\" to move left & right.       "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "  Press any button to exit.                                           "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ║\033[0m"
              << "                                                                      "
              << "\033[34m║      \033[0m" << std::endl
              << "\033[34m           ╚══════════════════════════════════════════════════════════════════════╝      \033[0m" << std::endl;

    getch();
}
