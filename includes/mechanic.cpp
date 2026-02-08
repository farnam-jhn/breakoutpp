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
extern int bricksCount;


void ballmover(Ball &ball){

    if (player.health == 0){
        player.gameover = true;
    }
    else if (bricksCount == 0){
        player.won = true;
    }

    using namespace std::chrono_literals;

    // Calculate new position
    int tempNewX = ball.loc.x + ball.v.vX;
    int tempNewY = ball.loc.y + ball.v.vY;

    // Checking collision for current position
    for(int i = 0; i < 36; i++){
        if(bricks_idx[i] != -1 && bricks_idy[i] != -1){
            int brick_row = bricks_idx[i];
            int brick_col_start = bricks_idy[i];
            
            // Check if ball is stuck in a brick
            if(ball.loc.y == brick_row && 
               ball.loc.x >= brick_col_start && 
               ball.loc.x <= brick_col_start + 4){
                // reverse both velocities
                ball.v.vX = -ball.v.vX;
                ball.v.vY = -ball.v.vY;
                tempNewX = ball.loc.x + ball.v.vX;
                tempNewY = ball.loc.y + ball.v.vY;
                // delete brick and add score
                player.score += 1000;
                bricksCount--;
                bricks_idx[i] = -1;
                bricks_idy[i] = -1;
                
                goto skip_normal_collision;  // Skip rest of collision checks
            }
        }
    }
    
    // Checking brick collison for new position
    for(int i = 0; i < 36; i++){
        if(bricks_idx[i] != -1 && bricks_idy[i] != -1){
            int brick_row = bricks_idx[i];
            int brick_col_start = bricks_idy[i];
            int brick_col_end = brick_col_start + 4;
            
            // checking if there is a brick there, Works like (isBrick( , )) function
            if(tempNewY == brick_row && 
               tempNewX >= brick_col_start && 
               tempNewX <= brick_col_end){
                
                bool bounceX = false;
                bool bounceY = false;
                
                // X direction
                if(ball.v.vX > 0 && ball.loc.x < brick_col_start){ // heading right
                    bounceX = true;
                }
                else if(ball.v.vX < 0 && ball.loc.x > brick_col_end){ // heading left
                    bounceX = true;
                }
                
                // Y direction
                if(ball.v.vY > 0 && ball.loc.y < brick_row){ // heading down
                    bounceY = true;
                }
                else if(ball.v.vY < 0 && ball.loc.y > brick_row){ // heading up
                    bounceY = true;
                }
                
                if(bounceX && bounceY){ // Corner hit
                    ball.v.vX = -ball.v.vX;
                    ball.v.vY = -ball.v.vY;
                }
                else if(bounceX){ // Side hit
                    ball.v.vX = -ball.v.vX;
                }
                else { // Top/bottom hit
                    ball.v.vY = -ball.v.vY;
                }
                
                // Recalculate position after bounce
                tempNewX = ball.loc.x + ball.v.vX;
                tempNewY = ball.loc.y + ball.v.vY;
                
                // delete brick and add score
                player.score += 1000;
                bricksCount--;
                bricks_idx[i] = -1;
                bricks_idy[i] = -1;
                
                break;  // Only handle one brick per frame
            }
        }
    }
    
    skip_normal_collision:
    
    // Wall collision
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
