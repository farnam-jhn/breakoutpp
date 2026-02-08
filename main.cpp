// Headers

#include "includes/menu.h"
#include "includes/getchar.h"
#include "includes/board.h"
#include "includes/cursorhide.h"
#include "includes/structs.h"
#include "includes/mechanic.h"
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>

using namespace std::chrono;


// ----- Global variables -----

// Game components
int board_lenght = 80;
int board_width = 30;
std::string board[30][80];
std::string hud[30][20];
int hudLength = 20;
int hudWidth = 30;
int velocitySpeed[3] = {60,70,80};
int bricksCount = 36;
Paddle paddle;
Ball ball;
Player player;

Brick* bricks = nullptr;
int bricks_idx[36], bricks_idy[36];

// Characters

std::string ballChar = "\033[32m●\033[0m";
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


// ----- Functions prototype -----

void setup();
void deallocation();
void locatePaddle(int x);
void boardRender();
void ballMoveTask();
void endGame();

// ----- Main function -----

std::atomic<bool> running(true); /* used in order to manage the thread
                                    and prevent threads racing (racing : a thread reading
                                    a variable created by another when it's not fully written) */

int main(){

    using namespace std::chrono;

    show_console_cursor(false); // hides the cursor

    // Unicode settings

    system("chcp 65001"); // for showing the unicode characters in terminal

    // Menu

    while (true) {
        system("clear");
        char opt = optionChoosenByUser();
        switch (opt) {
            case '1':
            { // written in scope to maintain the threads
                system("clear");
                std::cout << "\n\n    Enter your name : ";
                std::cin >> player.name;

                system("clear");

                std::cout << "\n\n    PRESS ANY KEY TO START THE GAME. \n";

                getch();
                std::thread threadOne(boardRender); // creates a thread for board rendering
                std::thread threadTwo(ballMoveTask); // created a thread for ball movement

                system("clear");
                setup(); // sets up the board
                while (true){
                    int q = inputProccessing(paddle);
                    if (q == 0){
                        break;
                    }
                }



                threadOne.join();
                threadTwo.join();

                running = true;  // opens the thread for new game

                deallocation(); // de allocates the array in the heap
            }
            break;
            case '2':
                helpMenu();
            break;
            case '3':
            // TODO : Game history
            break;
            case '4':
                system("clear");
                std::cout << std::endl;
                std::cout << "  Press \"c\" to confirm\n";
                char confirmChar = getch();
                if (confirmChar == 'c'){
                    system("clear");
                    return 0;
                }
                system("clear");
            break;

        }
    }

}

// ----- Functions -----

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

    // setup ball
    ball.loc.x = 22;
    ball.loc.y = 15;

    /* Note : the velocity below is not suitable for configuring the speed
    in order to change the speed, change the value of interval in ballMoveTask
    changing the velocity below would affect the ball collision angle.*/

    ball.v.vX = 1;
    ball.v.vY = 1;

    board[ball.loc.y][ball.loc.x] = ballChar;

}

// deallocating board from heap

void deallocation(){
    delete[] bricks;
}

// Board rendering

void boardRender() {

    auto interval = milliseconds(16);
    auto next_time = steady_clock::now();

    while (running) {
        next_time += interval;
        drawBoard();
        std::this_thread::sleep_until(next_time);
    }

}

// Ball rendering

void ballMoveTask(){

    auto next_time = steady_clock::now();

    while (running) {
        auto interval = milliseconds(velocitySpeed[abs(ball.v.vX) - 1]);
        next_time += interval;
        ballmover(ball);

        if (player.gameover || player.won){
            running = false; // closes the threads
            std::this_thread::sleep_for(milliseconds(100));
            system("clear");
            endGame();
            std::cout << "\n\n    Press any key to continue\n";
            getch();
        }

        std::this_thread::sleep_until(next_time);
    }

}

void endGame(){

    // Reporting

    if (player.gameover){
        std::cout << "\n\n    Game over.\n";
    }else {
        std::cout << "\n\n    Game finished. \n    Congrats! You Won!";
    }

    std::cout << "\n    Your score : ";
    std::cout << player.score;

}
