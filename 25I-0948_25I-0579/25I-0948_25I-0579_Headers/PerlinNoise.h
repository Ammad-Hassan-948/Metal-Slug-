#pragma once
#include<cmath>
//normal rand functions give uncorrelated values
// perlin noise function give smooth, deterministic, bounded values between -1 and 1

class PerlinNoise {

public:
	
	PerlinNoise(unsigned int seed);//seed ot determine the unique gradient; same seed same output

	double noise1D(double x) const;//evaluating noise at x return bw -1 and 1

private:

	int p[512]; // permutation table of 512 entires half are duplicated
	// to map the lattice point integers to random gradients


	static double fade(double t); //fade curve of the equation of 6t power 5 - 15t power 4 + 10t power 3

	static double lerp(double a, double b, double t);
	//linear interpolation
	//if t = 0, a; if t = 1, then b

	static double grad1D(int hash, double x);//1d gradient; picks gradient direction from +1 to -1
	//then returns dot product with the offset; might do this for the four cornes




};