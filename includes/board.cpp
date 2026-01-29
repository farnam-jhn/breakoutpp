// Headers
#include <iostream>
#include "getchar.h"
#include "clear.h"
#include "board.h"
using namespace std;

// Structures

// Global varialbes

extern char board[30][80];
extern int board_width;
extern int board_lenght;
extern int bricks_idx[36], bricks_idy[36];

// Functions

void drawBoard(){

    clear();
    char current_char;
    for(int i = 0; i < board_width; i++){
        for(int j = 0; j < board_lenght; j++){
            current_char = board[i][j];
            switch(current_char)
            {
            case '-': // borders
            case '|':
            case '+':
                cout << current_char;
                break;
            case '#': // brick
                cout << "#####";
                j += 4;
                break;
            case '=': // paddle
                cout << "==========";
                j += 9;
                break;
            default:
                cout << ' ';
                break;
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