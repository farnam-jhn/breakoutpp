// Headers
#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <random>
#include "clear.h"
#include "getchar.h"
#include "setcursor.h"
#include "structs.h"
using namespace std;

// Structures

// Global varialbes

extern string board[30][80];
extern int board_width;
extern int board_lenght;
extern int bricks_idx[36], bricks_idy[36];

extern std::string block ;
extern std::string blockRed ;
extern std::string blockGreen;
extern std::string blockBlue ;
extern std::string blockYellow ;
extern std::string trCorner ;
extern std::string tlCorner ;
extern std::string brCorner ;
extern std::string blCorner ;
extern std::string paddeleLine ;
extern std::string horizontalLine ;
extern std::string verticalLine ;

// Functions

void drawBoard(){

    gotoxy(0, 0);
    string currentChar;
    cout << endl << endl;
    for(int i = 0; i < board_width; i++){
        cout << "    ";
        for(int j = 0; j < board_lenght; j++){
            currentChar = board[i][j];
            if (currentChar == horizontalLine ||
                currentChar == verticalLine ||
                currentChar == tlCorner ||
                currentChar == trCorner ||
                currentChar == blCorner ||
                currentChar == brCorner){
                    cout << currentChar;
            }
            else if (currentChar == block) {

                // first we shuffle colors based on the line

                std::mt19937 gen(i+1);
                std::vector<std::string> colors = {blockRed, blockBlue, blockGreen, blockYellow, block};
                std::shuffle(colors.begin(), colors.end(), gen);

                for(const auto& color : colors) {
                    std::cout << color;
                }
                j += 4;
            }
            else if (currentChar == paddeleLine){
                for (int k = 0 ; k < 10 ; k++){
                    cout << paddeleLine;
                }
                j += 9;
            }
            else {
                    cout << " ";
            }
        }
        cout << endl;

    }
}

// checking if a certain location contains a brick or not
bool isBrick(int x, int y){
    for(int i = 0, j = 0; i < 36; i++, j++){
        if(bricks_idx[i] == x){
            if(bricks_idy[i] == y){
                return true;
            }
        }
    }
    return false;
}

// Proccessing input

int inputProccessing(Paddle &paddle){

    using namespace std::chrono_literals; // for sleep function

    char inputChar = getch();
    bool moved = false;
    int temp = paddle.start_loc.x;
    switch (inputChar) {
        case 'a' :
            if (paddle.start_loc.x > 1){
                paddle.start_loc.x--;
                moved = true;
            }
        break;
        case 'A' :
            if (paddle.start_loc.x > 1){
                paddle.start_loc.x--;
                moved = true;
            }
        break;
        case 'd' :
            if (paddle.start_loc.x + 10 < board_lenght - 1){
                paddle.start_loc.x++;
                moved = true;
            }
        break;
        case 'D' :
            if (paddle.start_loc.x + 10 < board_lenght - 1){
                paddle.start_loc.x++;
                moved = true;
            }
        break;
        case 'q':
            return 0;
        break;
        case 'Q':
            return 0;
        break;

        default:
            cout << "Error : Invalid input";
            std::this_thread::sleep_for(200ms);
            gotoxy(0, 33);
            cout << "                                                                               ";
            return 1;
            clear();
    }

    // Changing paddle location

    if (moved){
        board[board_width - 2][paddle.start_loc.x] = paddeleLine;
        board[board_width - 2][temp] = " ";
    }


    return 1;
}
