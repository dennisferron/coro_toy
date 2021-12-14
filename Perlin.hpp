#pragma once

#include "Vector2.hpp"

#include <vector>

class Perlin
{
private:
	std::vector<int> P;

	Vector2 GetConstantVector(int v) const;
	double Fade(double t) const;
	double Lerp(double t, double a1, double a2) const;
	
public:
	Perlin();
	double Noise2D(double x, double y) const;
	double octave_noise(double x, double y) const;
};

