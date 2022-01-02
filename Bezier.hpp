#pragma once

#include "Vector2.hpp"

class Bezier
{
private:
    Vector2 p0;
    Vector2 p1;
    Vector2 p2;
public:
    Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2);
    Vector2 pos_at(double const& t) const;
    Vector2 normal_at(double const& t) const;
};


