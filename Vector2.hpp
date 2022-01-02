#pragma once

#include "math.h"

struct Vector2
{
    double x;
    double y;

    Vector2() : x(0), y(0) {}

    Vector2(double x, double y) :
        x(x), y(y) {}

    double dot(Vector2 const& other) const
    {
        return x*other.x + y*other.y;
    }

    Vector2 rotate90() const
    {
        return { -y, x };
    }

    Vector2 normalize() const
    {
        double d = sqrt(x*x + y*y);
        return { x/d, y/d };
    }

    friend Vector2 operator *(double const& a, Vector2 const& b)
    {
        return { a*b.x, a*b.y };
    }

    friend Vector2 operator *(Vector2 const& a, double b)
    {
        return { a.x*b, a.y*b };
    }

    friend Vector2 operator +(Vector2 const& a, Vector2 const& b)
    {
        return { a.x+b.x, a.y+b.y };
    }
};

