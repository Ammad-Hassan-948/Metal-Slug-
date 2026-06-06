#include "FractalNoise.h"

FractalNoise::FractalNoise(unsigned int seed, int octaves, double frequency, double amplitude, double persistence, double lacunarity)
:perlin(seed), octaves(octaves), frequency(frequency), amplitude(amplitude),
persistence(persistence), lacunarity(lacunarity)

{}

double FractalNoise::sample(double x) const
{
	double total = 0.0f;

	double amp = amplitude; //will shrink each octave

	double freq = frequency; // grows each octave

	double maxValue = 0.0f;


	for (int i = 0; i < octaves; i++) {

		total += perlin.noise1D(x * freq) * amp;
		maxValue += amp;


		amp *= persistence;//shrinks
		freq *= lacunarity;//grows

	}


	return total / maxValue;//normalizing to keep values between -1 and 1
}




