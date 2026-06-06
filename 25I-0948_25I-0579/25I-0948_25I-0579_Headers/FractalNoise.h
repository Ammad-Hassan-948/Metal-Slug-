#pragma once
#include "PerlinNoise.h"


//fractal noise is just achieved by summed up perlin calls called octaves
//to get both large features like mountains and small like bumps, rocks etc

//each octave has higher frequency then its smaller, tighter features
// lower amplitude contributes less to the total

//an octave with wide hills has low frequency and the one with minute details has highest frequency

class FractalNoise {
private:

	PerlinNoise perlin;

	int octaves;

	double frequency;

	double amplitude;
	double persistence;

	double lacunarity;


	//octaves is num of layers, more will lead to richer details
//low frequency will lead to wider, more spread features

//persistence is how fast amplitude shrinks each octave nd lacunarity is how fast frequency grows
// each octave it allows us to know how much its zoomed in


public:

	FractalNoise(unsigned int seed, int octaves, double frequency, double amplitude,

		double persistence, double lacunarity);

	double sample(double x) const;
	//sample fractal noise at pos x


};