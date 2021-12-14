#include "Texture.hpp"

Texture::Texture(Color low_color, Color high_color)
    : noise(), low_color(low_color), high_color(high_color)
{
}

Color Texture::color_at(double x, double y)
{
    constexpr double root_two = 1.4142;

    double scaled_height = 0.5*(
            noise.octave_noise(x, y) / root_two
    ) + 0.5;

    return low_color.fade_to(high_color, scaled_height);
}
