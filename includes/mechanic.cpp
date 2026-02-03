#include "structs.h"
#include "board.h"
#include <string>
#include <thread>

using namespace std;

extern Ball ball;
extern int board_lenght;
extern int board_width;
extern string board[30][80];
extern string ballChar;
extern int bricks_idx[36];
extern int bricks_idy[36];

void ballmover(Ball &ball){
    using namespace std::chrono_literals;
    // Clear old position
    board[ball.loc.y][ball.loc.x] = " ";

    // Calculate new position
    int tempNewX = ball.loc.x + ball.v.vX;
    int tempNewY = ball.loc.y + ball.v.vY;

    int brick_tempNewX, brick_tempNewY = tempNewY;
    for(int i = tempNewX; i > 0; i--){
        if(i % 5 == 0){
            brick_tempNewX = i;
            break;
        }
    }
    int brick_index = (brick_tempNewY - 1) * 12 + (brick_tempNewX / 5) - 2;
    if(isBrick(brick_tempNewY, brick_tempNewX)){
        if(ball.v.vX > 0){ // heading right
            if(bricks_idx[brick_index - 1] == -1 && brick_tempNewX == tempNewX){
                ball.v.vX = -ball.v.vX;
                tempNewX = ball.loc.x + ball.v.vX;
            }
            else{
                ball.v.vY = -ball.v.vY;
                tempNewY = ball.loc.y + ball.v.vY;
            }
        }
        else{ // heading left
            if(bricks_idx[brick_index + 1] == -1 && brick_tempNewX + 4 == tempNewX){
                ball.v.vX = -ball.v.vX;
                tempNewX = ball.loc.x + ball.v.vX;
            }
            else{
                ball.v.vY = -ball.v.vY;
                tempNewY = ball.loc.y + ball.v.vY;
            }
        }
     

        // deleting the brick
        board[brick_tempNewY][brick_tempNewX] = " ";
        bricks_idx[brick_index] = -1;
        bricks_idy[brick_index] = -1;
    }
    else{
        if (tempNewX <= 0 || tempNewX >= board_lenght - 1){
            ball.v.vX = -ball.v.vX;
            tempNewX = ball.loc.x + ball.v.vX;
        }

        if (tempNewY <= 0 || tempNewY >= board_width - 1){
            ball.v.vY = -ball.v.vY;
            tempNewY = ball.loc.y + ball.v.vY;
        }
    }


    // Update position
    ball.loc.x = tempNewX;
    ball.loc.y = tempNewY;

    // Draw ball at new position
    board[ball.loc.y][ball.loc.x] = ballChar;
}
