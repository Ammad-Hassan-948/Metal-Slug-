#include "PerlinNoise.h"
#include <cmath>

PerlinNoise::PerlinNoise(unsigned int seed)
{
	//filling the permuatation table with index values

	int permutationTable[256];

	for (int i = 0; i < 256; i++) {

		permutationTable[i] = i;
	}

	unsigned int lcg = seed;
	//linear congruential generator is a simple math formula that generates sequence of 
	// random values which 
	//are actually related to one another


	//fisher yates algorithm simply picks a value from the end, picks a random spot before it
	//using lcg and swap the two numbers

	//the list becomes scrambled but is not random and depends on the seed

	for (int i = 255; i > 0; i--) {

		lcg = lcg * 1664525u + 1013904223u;

		int j = (int)(lcg % (unsigned int)(i + 1));

		int temp = permutationTable[i];

		permutationTable[i] = permutationTable[j];

		permutationTable[j] = temp;
	}


	for (int i = 0; i < 256; i++) {

		p[i] = permutationTable[i];

		p[i + 256] = permutationTable[i];

	}
}


double PerlinNoise::fade(double t) {// the fractional difference is passed to the fade function
	return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

double PerlinNoise::lerp(double a, double b, double t) {

	return	a + t * (b - a);
}

double PerlinNoise::grad1D(int hash, double x) {

	return (hash & 1) ? -x : x;

//1d gradients are bw -1 and 1
	//lowest bit of hash picks the direction and dot project is gradient * x
}

double PerlinNoise::noise1D(double x) const {

	int xi = (int)floor(x) & 255;//integer lattic point to the left of the operand
	//if we go to 256, by doing & 255, it will return to 0 so this allows for an infinite world

	double xf = x - floor(x); //fractional offset from the left lattice point 
	//xf is always between 0 and 1

	double u = fade(xf); // u will be 0 at left lattice and 1 at right lattice point


	//hash pseudo random selector for each permutation table

	int hashLeft = p[xi];
	int hashRight = p[xi + 1];

	double gradLeft = grad1D(hashLeft, xf); double gradRight = grad1D(hashRight, xf - 1.0);

	return lerp(gradLeft, gradRight, u);//linear interpolation for smooth blend between right and left
}

