#pragma once

#include "Texture.hpp"

#include <windows.h>

#include <memory>

class Snake
{
private:
    std::shared_ptr<Texture> texture;
public:
    Snake(std::shared_ptr<Texture> texture);
    void draw(HDC hdc);
};


