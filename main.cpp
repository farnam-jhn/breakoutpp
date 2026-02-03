// Headers

#include "includes/menu.h"
#include "includes/getchar.h"
#include "includes/clear.h"
#include "includes/board.h"
#include "includes/cursorhide.h"
#include "includes/structs.h"
#include <string>
#include <chrono>
#include <thread>
#include <atomic>


// Global variables

int board_lenght = 80;
int board_width = 30;
std::string board[30][80];

std::string block = "█";
std::string blockRed = "\033[31m█\033[0m";
std::string blockGreen= "\033[32m█\033[0m";
std::string blockBlue = "\033[34m█\033[0m";
std::string blockYellow = "\033[33m█\033[0m";
std::string trCorner = "\033[34m╗\033[0m";
std::string tlCorner = "\033[34m╔\033[0m";
std::string brCorner = "\033[34m╝\033[0m";
std::string blCorner = "\033[34m╚\033[0m";
std::string paddeleLine = "\033[32m╍\033[0m";
std::string horizontalLine = "\033[34m═\033[0m";
std::string verticalLine = "\033[34m║\033[0m";

Paddle paddle;

Brick* bricks = nullptr;
int bricks_idx[36], bricks_idy[36];

// Functions prototype

void ballLocationFunction(Location loc, double slope, double hDistance);
void setup();
void deallocation();
void locatePaddle(int x);
void backgroundTask();

// Main function

std::atomic<bool> running(true);

int main(){

    using namespace std::chrono;

    // Unicode settings
    system("chcp 65001"); // for showing the unicode characters in terminal
    show_console_cursor(false);
    // Menu

    while (true) {
        clear();
        char opt = optionChoosenByUser();
        switch (opt) {
            case '1':
            {
                std::thread background_thread(backgroundTask);
                clear();
                setup();
                while (true){
                    int q = inputProccessing(paddle);
                    if (q == 0){
                        break;
                    }
                }
                getch();

                running = false;
                background_thread.join();
                running = true;  // Reset for next game

                deallocation();
            }
            break;
            case '2':
                helpMenu();
            break;
            case '3':
            // TODO
            break;
            case '4':
                clear();
                std::cout << std::endl;
                std::cout << "  Press \"c\" to confirm\n";
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

void locatePaddle(int x){ // receives starting point x because y stays the same
    board[board_width - 2][x] = paddeleLine;
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
        board[0][i] = horizontalLine; // top
        board[board_width - 1][i] = horizontalLine; // bottom
    }
    for(int i = 1; i < board_width - 1; i++){
        board[i][0] = verticalLine; // right
        board[i][board_lenght - 1] = verticalLine; // left
    }
    // setting up corners
    board[0][0] = tlCorner;
    board[0][board_lenght - 1] = trCorner;
    board[board_width - 1][0] = blCorner;
    board[board_width - 1][board_lenght - 1] = brCorner;

    // setting up bricks
    for(int i = 1; i <= 3; i++){
        for(int j = 1; j < board_lenght - 1; j++){
            if(isBrick(i, j)){
                board[i][j] = block;
                j += 4;
            }
        }
    }

    // setup paddle
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

// For board draw

void backgroundTask() {
    using namespace std::chrono;

    auto interval = milliseconds(10);
    auto next_time = steady_clock::now();

    while (running) {
        next_time += interval;
        drawBoard();
        std::this_thread::sleep_until(next_time);
    }
}
