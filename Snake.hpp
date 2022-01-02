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

    static constexpr double scale_spacing = 10;
    static constexpr double scale_radius = 7;
    static constexpr int scale_rows = 6;
    static constexpr int scale_cols = 40;
    static constexpr double scales_height = scale_rows * scale_spacing;
    static constexpr double scales_width = scale_cols * scale_spacing;
    static constexpr RECT texture_rect = {10, 20, 410, 80 };

    Vector2 transform(Vector2 in) const;

public:
    Snake(std::shared_ptr<Texture> texture);
    void draw(HDC hdc);
    void step_animation(unsigned int delta_ms);
};


