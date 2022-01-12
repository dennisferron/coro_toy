#pragma once

#include "Snake.hpp"

#include <vector>

class SnakeBoard
{
private:
    std::vector<Snake> snakes;

public:
    SnakeBoard();
    void draw(HDC hdc);
    void step_animation(unsigned int delta_ms);
};


