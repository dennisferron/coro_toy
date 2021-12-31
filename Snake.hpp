#pragma once

#include "Texture.hpp"
#include "Vector2.hpp"

#include <windows.h>

#include <memory>

class Snake
{
private:
    std::shared_ptr<Texture> texture;
    double phase = 0.0;
    double phase_dir = 1.0;

    Vector2 transform(Vector2 in) const;

public:
    Snake(std::shared_ptr<Texture> texture);
    void draw(HDC hdc);
    void step_animation(unsigned int delta_ms);
};


