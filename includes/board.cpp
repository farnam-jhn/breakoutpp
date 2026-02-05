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

// Global varialbes

extern string board[30][80];
extern string hud[30][20];
extern int board_width;
extern int board_lenght;
extern int bricks_idx[36], bricks_idy[36];
extern int hudLength;
extern int hudWidth;

extern string ballChar ;
extern string block ;
extern string blockRed ;
extern string blockGreen;
extern string blockBlue ;
extern string blockYellow ;
extern string trCorner ;
extern string tlCorner ;
extern string brCorner ;
extern string blCorner ;
extern string paddeleLine ;
extern string horizontalLine ;
extern string verticalLine ;
extern Player player;

// Function Prototypes

void hudCalculation();
string scoreInString();
// Functions

bool isBrick(int, int);

void drawBoard(){

    hudCalculation();
    gotoxy(0, 0);
    string currentChar;
    cout << endl << endl;
    for(int i = 0; i < board_width; i++){
        cout << "    ";
        for(int j = 0; j < board_lenght + hudLength ; j++){
            if (j < hudLength){
                cout << hud[i][j];
            }
            else {
                int boardCol = j - hudLength;
                currentChar = board[i][boardCol];
                if (currentChar == horizontalLine ||
                    currentChar == verticalLine ||
                    currentChar == tlCorner ||
                    currentChar == trCorner ||
                    currentChar == blCorner ||
                    currentChar == brCorner ||
                    currentChar == ballChar){
                        cout << currentChar;
                }
                else if (isBrick(i, boardCol)) {

                    int nameSeed1 = (int)player.name[0];
                    int nameSeed2 = (int)player.name[1];

                    std::mt19937 gen(i * nameSeed1 + j * nameSeed2);  // generates a random based on seed (a combination of i and j with player's name)

                    std::vector<std::string> colors = {blockRed, blockBlue, blockGreen, blockYellow, block}; // Creates a dynamic array containing the colored blocks characters
                    std::shuffle(colors.begin(), colors.end(), gen); // shuffles the colors dynamic array

                    for(int k = 0; k < 5; k++) {
                        std::cout << colors[0];
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

// Head up display

void hudCalculation(){

    // setting up borders
    for(int i = 1; i < hudLength - 1; i++){
        hud[0][i] = horizontalLine; // top
        hud[hudWidth - 1][i] = horizontalLine; // bottom
    }
    for(int i = 1; i < hudWidth - 1; i++){
        hud[i][0] = verticalLine; // right
        hud[i][hudLength - 1] = verticalLine; // left
    }
    // setting up corners

    hud[0][0] = tlCorner;
    hud[0][hudLength - 1] = trCorner;
    hud[hudWidth - 1][0] = blCorner;
    hud[hudWidth - 1][hudLength - 1] = brCorner;

    for (int i = 1; i < hudWidth - 1; i++){
        for (int j = 1; j < hudLength - 1; j++){
            hud[i][j] = " ";
        }
    }


    string score = " Score : " + scoreInString();
    for (int i = 0; i < 15; i++){
        hud[2][i + 2] = score[i];
    }

}

// Proccessing input

int inputProccessing(Paddle &paddle){

    using namespace std::chrono_literals; // for sleep function

    char inputChar = getch();
    bool moved = false;
    int temp = paddle.start_loc.x;
    switch (inputChar) {
        case 'a' :
        case 'A' :
        if (paddle.start_loc.x > 1) {
            paddle.start_loc.x -= 3;

            if (paddle.start_loc.x < 1) {
                paddle.start_loc.x = 1;
            }
            moved = true;
        }
        break;
        case 'd' :
        case 'D' :
            if (paddle.start_loc.x < board_lenght - 11) {

                paddle.start_loc.x += 3;

                if (paddle.start_loc.x > board_lenght - 11) {
                    paddle.start_loc.x = board_lenght - 11;
                }
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

string scoreInString(){
    string result = to_string(player.score);
    result.insert(0, 6 - result.length(), '0');
    return result;
}
