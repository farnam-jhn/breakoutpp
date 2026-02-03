#pragma once
#include <string>

struct Palyer{
    int score;
    std::string name;
};

struct Location{
    int x;
    int y;
};

struct Brick{
    Location loc;
    int width;
    int lenght;
    bool alive;
    int score;
};

struct Paddle{
    Location start_loc;
    // int lenght; // possible feature, right now considered 10
};
