#pragma once

struct Color
{
    double R;
    double G;
    double B;

    Color(double R, double G, double B) : R(R), G(G), B(B) {}
    Color(int R, int G, int B) : R(R/255.0), G(G/255.0), B(B/255.0) {}

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


