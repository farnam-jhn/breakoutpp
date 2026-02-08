#include "structs.h"
#include "board.h"
#include <string>
#include <thread>

using namespace std;

extern Ball ball;
extern Player player;
extern int board_lenght;
extern int board_width;
extern string board[30][80];
extern string ballChar;
extern int bricks_idx[36];
extern int bricks_idy[36];
extern string paddeleLine ;
extern Paddle paddle;


void ballmover(Ball &ball){

    if (player.health == 0){
        player.gameover = true;
    }

    using namespace std::chrono_literals;

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

        // deleting the brick and adding the score
        board[brick_tempNewY][brick_tempNewX] = " ";
        player.score += 1000;
        bricks_idx[brick_index] = -1;
        bricks_idy[brick_index] = -1;
    }
    else{
        if (tempNewX <= 0 || tempNewX >= board_lenght - 1){
            ball.v.vX = -ball.v.vX;
            tempNewX = ball.loc.x + ball.v.vX;
        }

        if (tempNewY == board_width - 1){
            player.health--;
            ball.v.vY = -ball.v.vY;
            tempNewY = ball.loc.y + ball.v.vY;
        }
        else if (tempNewY <= 0 || tempNewY >= board_width - 1){
            ball.v.vY = -ball.v.vY;
            tempNewY = ball.loc.y + ball.v.vY;
        }



        if (tempNewY == board_width - 2) {
            // Check if the ball's X position is inside the paddle (width 10)
            if (tempNewX >= paddle.start_loc.x && tempNewX < paddle.start_loc.x + 10) {

                int distanceFromPS = tempNewX - paddle.start_loc.x;

                ball.v.vY = -1; // Force ball to move UP

                int velocityMagnitude[10] = {3,2,2,1,1,1,1,2,2,3}; // an array that gives any x axis distance between the ball and paddle start a velocity

                if (ball.v.vX > 0){
                    ball.v.vX = velocityMagnitude[distanceFromPS];
                }
                else {
                    ball.v.vX = -velocityMagnitude[distanceFromPS];
                }

                tempNewY = ball.loc.y + ball.v.vY; // Update next Y immediately

            }
        }
    }

    // Clear old position

    if (ball.loc.x != tempNewX || ball.loc.y != tempNewY) {
        board[ball.loc.y][ball.loc.x] = " ";
    }

    // Update position
    ball.loc.x = tempNewX;
    ball.loc.y = tempNewY;


    // Draw ball at new position
    board[ball.loc.y][ball.loc.x] = ballChar;
}
