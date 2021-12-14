#include "Bezier.hpp"

Vector2 quadratic_bezier(
        double const& t,
        Vector2 const& p0,
        Vector2 const& p1,
        Vector2 const& p2)
{
    // Equation from Wikipedia article on Bezier curves:
    return (1-t)*(1-t)*p0 + 2*(1-t)*t*p1 + t*t*p2;
}

Vector2 tangent_bezier(
        double const& t,
        Vector2 const& p0,
        Vector2 const& p1,
        Vector2 const& p2)
{
    // What WolframAlpha spit out for d/dt of Bezier equation:
    return (2*t-2)*p0 + (2-4*t)*p1 + 2*t*p2;
}

Vector2 normal_bezier(
        double const& t,
        Vector2 const& p0,
        Vector2 const& p1,
        Vector2 const& p2)
{
    Vector2 tangent = tangent_bezier(t, p0, p1, p2);
    return tangent
        .rotate90()
        .normalize();
}
