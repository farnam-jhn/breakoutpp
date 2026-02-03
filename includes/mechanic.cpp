#include "structs.h"
#include <string>

using namespace std;

extern Ball ball;
extern int board_lenght;
extern int board_width;
extern string board[30][80];
extern string ballChar;

void ballmover(Ball &ball){
    // Clear old position
    board[ball.loc.y][ball.loc.x] = " ";

    // Calculate new position
    int tempNewX = ball.loc.x + ball.v.vX;
    int tempNewY = ball.loc.y + ball.v.vY;

    if (tempNewX <= 0 || tempNewX >= board_lenght - 1){
        ball.v.vX = -ball.v.vX;
        tempNewX = ball.loc.x + ball.v.vX;
    }

    if (tempNewY <= 0 || tempNewY >= board_width - 1){
        ball.v.vY = -ball.v.vY;
        tempNewY = ball.loc.y + ball.v.vY;
    }

    // Update position
    ball.loc.x = tempNewX;
    ball.loc.y = tempNewY;

    // Draw ball at new position
    board[ball.loc.y][ball.loc.x] = ballChar;
}
