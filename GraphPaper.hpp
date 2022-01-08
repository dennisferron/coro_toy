#pragma once

#include <windows.h>

class GraphPaper
{
public:
    static constexpr double square_size = 40;

private:
    RECT rect;

public:
    GraphPaper(RECT const& rect);
    void draw(HDC hdc);
};


