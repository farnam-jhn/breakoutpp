// Headers

#include "includes/menu.h"
#include "includes/getchar.h"
#include "includes/clear.h"
#include "includes/board.h"
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

struct Brick{
    Location loc;
    int width;
    int lenght;
    bool alive;
    int score;
};

struct Paddle{
    Location start_loc;
    // int lenght; // possible feature, right now considered 10
};

// Global variables

int board_lenght = 80;
int board_width = 30;
char board[30][80];

Brick* bricks = nullptr;
int bricks_idx[36], bricks_idy[36];

// Functions prototype

void ballLocationFunction(Location loc, double slope, double hDistance);
void setup();
void deallocation();
void locatePaddle(int x);

// Main function

int main(){

    // Unicode settings
    system("chcp 65001"); // for showing the unicode characters in terminal

    // Menu

    while (true) {
        clear();
        char opt = optionChoosenByUser();
        switch (opt) {
            case '1':
                setup();
                drawBoard();
                getch(); // temporary
                deallocation();
            break;
            case '2':
            // TODO
            break;
            case '3':
            // TODO
            break;
            case '4':
                std::cout << "Press \"c\" to confirm";
                char confirmChar = getch();
                if (confirmChar == 'c'){
                    return 0;
                }
            break;

        }
    }

}

// Functions

void ballLocationFunction(Location loc, double slope, double hDistance){

    // y = ax + b

    loc.y = (double)loc.x * slope + hDistance;

}

void locatePaddle(int x){ // receives starting point x because y stays the same
    board[board_width - 2][x] = '=';
}

// setup the board when starting new game
void setup(){

    // setting up bricks
    bricks = new Brick[36]; // allocating board
    int counterX = 1, counterY = 10;
    for(int i = 0; i < 36; i++){ // saving the location of each brick
        bricks[i].loc.x = counterX;
        bricks[i].loc.y = counterY;
        bricks_idx[i] = counterX;
        bricks_idy[i] = counterY;
        counterY += 5;
        if(i == 11 || i == 23){
            counterY = 10;
            counterX++;
        }
    }
    /*
        11, 23 and 36 are being used as temporry numbers
        they should be replaced with variables made in the next levels of project
    */

    // setting up borders
    for(int i = 1; i < board_lenght - 1; i++){
        board[0][i] = '-'; // top
        board[board_width - 1][i] = '-'; // bottom
    }
    for(int i = 1; i < board_width - 1; i++){
        board[i][0] = '|'; // right
        board[i][board_lenght - 1] = '|'; // left
    }
    // setting up corners
    board[0][0] = '+';
    board[0][board_lenght - 1] = '+';
    board[board_width - 1][0] = '+';
    board[board_width - 1][board_lenght - 1] = '+';

    
    // setting up bricks
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j < board_lenght - 1; j++){
            if(isBrick(i, j)){
                board[i][j] = '#';
                j += 4;
            }
        }
    }

    // setup paddle
    Paddle paddle;
    paddle.start_loc.x = (board_lenght - 10) / 2 - 1;
    paddle.start_loc.y = board_width - 2;
    locatePaddle(paddle.start_loc.x);

    /*
        only the starting char of bricks and the paddle change. because it would be easier to layout them.
    */

}

// deallocatin board from heap
void deallocation(){
    delete[] bricks;
}

