#pragma once

struct Color
{
    double R;
    double G;
    double B;

    Color fade_to(Color const& x, double t)
    {
        auto lerp = [t](double a, double b)
            { return (1.0-t)*a + t*b; };

        return
        {
            lerp(R, x.R),
            lerp(G, x.G),
            lerp(B, x.B)
        };
    }

    int red_int() const
    {
        return static_cast<int>(255*R);
    }

    int green_int() const
    {
        return static_cast<int>(255*G);
    }

    int blue_int() const
    {
        return static_cast<int>(255*B);
    }
};


