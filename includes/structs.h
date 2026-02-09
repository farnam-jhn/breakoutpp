#pragma once
#include <string>

struct Player{
    int score = 0;
    std::string name;
    bool initialInput = false;
    int health = 3;
    bool gameover = false;
    bool won = false;
};

struct Location{
    int x;
    int y;
};

struct Brick{
    Location loc;
    int score;
};

struct Paddle{
    Location start_loc;
    // int lenght; // possible feature, right now considered 10
};

struct Velocity{
    int vX;
    int vY;
};

struct Ball{
    Location loc;
    Velocity v;
};
