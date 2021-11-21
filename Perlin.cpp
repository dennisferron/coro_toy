#include "Perlin.hpp"

#include <cstdlib>
#include <cmath>


Perlin::Perlin()
{
	// Enumerate
	for (int i = 0; i < 256; i++)
	{
		P.push_back(i);
	}

	// Shuffle	
	for (int e = P.size()-1; e > 0; e--)
	{
		int index = rand() % e;
		int temp  = P[e];
		
		P[e] = P[index];
		P[index] = temp;
	}
	
	// Duplicate
	for (int i = 0; i < 256; i++)
	{
		P.push_back(P[i]);
	}
}

Vector2 Perlin::GetConstantVector(int v) const
{
	//v is the value from the permutation table
	switch (v % 4)
	{
	case 0:
		return Vector2(1.0, 1.0);
	case 1:
		return Vector2(-1.0, 1.0);
	case 2:
		return Vector2(-1.0, -1.0);
	default:
		return Vector2(1.0, -1.0);
	}
}

double Perlin::Fade(double t) const
{
	return ((6*t - 15)*t + 10)*t*t*t;
}

double Perlin::Lerp(double t, double a1, double a2) const
{
	return a1 + t*(a2-a1);
}

double Perlin::Noise2D(double x, double y) const
{
	int X = static_cast<int>(floor(x)) % 256;
	int Y = static_cast<int>(floor(y)) % 256;

	double xf = x-floor(x);
	double yf = y-floor(y);

	auto topRight = Vector2(xf-1.0, yf-1.0);
	auto topLeft = Vector2(xf, yf-1.0);
	auto bottomRight = Vector2(xf-1.0, yf);
	auto bottomLeft = Vector2(xf, yf);
	
	//Select a value in the array for each of the 4 corners
	int valueTopRight = P[P[X+1]+Y+1];
	int valueTopLeft = P[P[X]+Y+1];
	int valueBottomRight = P[P[X+1]+Y];
	int valueBottomLeft = P[P[X]+Y];
	
	double dotTopRight = topRight.dot(GetConstantVector(valueTopRight));
	double dotTopLeft = topLeft.dot(GetConstantVector(valueTopLeft));
	double dotBottomRight = bottomRight.dot(GetConstantVector(valueBottomRight));
	double dotBottomLeft = bottomLeft.dot(GetConstantVector(valueBottomLeft));
	
	double u = Fade(xf);
	double v = Fade(yf);
	
	return Lerp(u,
				Lerp(v, dotBottomLeft, dotTopLeft),
				Lerp(v, dotBottomRight, dotTopRight)
			);

}

double Perlin::octave_noise(double x, double y) const
{
	double n = 0.0;
	double a = 1.0;
	double f = 0.005;
	
	for(int o = 0; o < 8; o++)
	{
		double v = a*Noise2D(x*f, y*f);
		n += v;
		
		a *= 0.5;
		f *= 2.0;
	}
	
	return n;
}
		