// Headers
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "setcursor.h"
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

void drawBoard() {

    std::string frame;
    frame.reserve(4000);   // جلوگیری از realloc

    frame += "\n\n";

    for (int i = 0; i < board_width; i++) {
        frame += "    ";

        for (int j = 0; j < board_lenght; j++) {
            const std::string& currentChar = board[i][j];

            if (currentChar == horizontalLine ||
                currentChar == verticalLine ||
                currentChar == tlCorner ||
                currentChar == trCorner ||
                currentChar == blCorner ||
                currentChar == brCorner) {

                frame += currentChar;
            }
            else if (currentChar == block) {

                // رنگ ثابت (بدون shuffle در هر فریم)
                frame += blockRed;
                frame += blockBlue;
                frame += blockGreen;
                frame += blockYellow;
                frame += block;

                j += 4;
            }
            else if (currentChar == paddeleLine) {

                for (int k = 0; k < 10; k++)
                    frame += paddeleLine;

                j += 9;
            }
            else {
                frame += ' ';
            }
        }
        frame += '\n';
    }

    // فقط یک بار چاپ
    std::cout << frame;
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

void inputProccessing(){

}
