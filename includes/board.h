#pragma once
#ifndef BOARD_H
#define BOARD_H
#include "getchar.h"
#include <iostream>

void drawBoard();
bool isBrick(int, int);
int inputProccessing(Paddle &paddle);

#endif
