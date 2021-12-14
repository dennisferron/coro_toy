#pragma once

#include "Perlin.hpp"
#include "Color.hpp"

class Texture
{
private:
    Perlin noise;
    Color low_color;
    Color high_color;

    static constexpr double lerp(double a, double b, double t)
    {
        return (1.0-t)*a + t*b;
    }
public:
    Texture(Color low_color, Color high_color);
    Color color_at(double x, double y);
};


