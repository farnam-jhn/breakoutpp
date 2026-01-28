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
            // TODO
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
