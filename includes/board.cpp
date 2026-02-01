// Headers
#include <iostream>
#include <string>
// #include "getchar.h"
#include "clear.h"
#include "board.h"
using namespace std;

// Structures

// Global varialbes

extern string board[30][80];
extern int board_width;
extern int board_lenght;
extern int bricks_idx[36], bricks_idy[36];


extern std::string block ;
extern std::string trCorner ;
extern std::string tlCorner ;
extern std::string brCorner ;
extern std::string blCorner ;
extern std::string paddeleLine ;
extern std::string horizontalLine ;
extern std::string verticalLine ;

// Functions

void drawBoard(){

    clear();
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
                for (int k = 0 ; k < 5 ; k++){
                    cout << block;
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
