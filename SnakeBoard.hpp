#pragma once

#include "Vector2.hpp"

#include <windows.h>
#include <vector>

class Snake;

class SnakeBoard
{
private:
    static constexpr int num_cols = 15;
    static constexpr int num_rows = 11;
    int board[num_cols][num_rows];
    std::vector<Snake> snakes;

public:
    SnakeBoard();
    void draw(HDC hdc);
    void step_animation(unsigned int delta_ms);
    bool request_cell(Vector2 pos);
    void return_cell(Vector2 pos);
};


