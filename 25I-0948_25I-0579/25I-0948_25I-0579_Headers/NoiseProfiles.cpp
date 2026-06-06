#include "NoiseProfiles.h"
#include"GameConstants.h"
#include <cmath>


static int clampInt(int val, int low, int high) {


	if (val < low)return low;
	if (val > high)return  high;

	return val;
}


//normal profile hardcoded
// 4 octaves, 0.0.4 frequency, 1.0 amplitude, 0.5 persistance, 2.0 lacunarity

NormalProfile::NormalProfile(unsigned int seed):noise(seed, 4, 0.04, 1.0, 0.5, 2.0)
, baseLine(30), variation(22), seaLevelValue(22), worldHeightValue(60)
{
}

int NormalProfile::getHeightAt(int worldX)
{
	double normalized = noise.sample((double)worldX);//to get normalized noise

	int height = baseLine + (int)(normalized * (double)variation);// linear mapping to block rows

	return clampInt(height, 1, worldHeightValue - 2);//to keep it inside the world rows
}

int NormalProfile::classifyBiome(int height)
{
	if (height < seaLevelValue) { return Biome::AQUATIC; }

	if (height >= 36) {
		return Biome::AERIAL;
	}

	return Biome::PLAINS;
}

int NormalProfile::getSeaLevel()
{
	return seaLevelValue;
}

int NormalProfile::getWorldHeight()
{
	return worldHeightValue;
}

const char* NormalProfile::getName()
{
	return "Normal";
}

AmplifiedProfile::AmplifiedProfile(unsigned int seed):noise(seed, 6, 0.035, 1.0, 0.55, 2.0), 
baseLine(28), variation(28), seaLevelValue(22), worldHeightValue(60)
{
}

int AmplifiedProfile::getHeightAt(int worldX)
{
	double normalized = noise.sample((double)worldX);

	//aplying square root to spread the absolute value outputs
	//positive mountains stay positive and negative abyss stays negative just magnitutde changed

	//the middle of the range will be pushed to the extremenes with very little middle ground for amplified pruposes

	if (normalized > 0.0) {
		normalized = sqrt(normalized);
	}

	else if (normalized < 0.0) {
		normalized = -sqrt(-normalized);
	}


	int height = baseLine + (int)(normalized * (double)variation);// linear mapping to block rows

	return clampInt(height, 1, worldHeightValue - 2);//to keep it inside the world rows
}

int AmplifiedProfile::classifyBiome(int height)
{
	if (height < seaLevelValue) { return Biome::AQUATIC; }

	if (height >= 40) { //higher threshold for taller peaks
		return Biome::AERIAL;
	}

	return Biome::PLAINS;
}

int AmplifiedProfile::getSeaLevel()
{
	return seaLevelValue;
}

int AmplifiedProfile::getWorldHeight()
{
	return worldHeightValue;
}

const char* AmplifiedProfile::getName()
{
	return "AMPLIFIED";
}




FlatProfile::FlatProfile(unsigned int seed):noise(seed, 2, 0.02, 1.0, 0.4, 2.0), baseLine(28),
variation(6), seaLevelValue(22), worldHeightValue(60)
//little variation only 2 octaves, smoother and less details
{
}

int FlatProfile::getHeightAt(int worldX)
{
	float normalized = noise.sample((double)worldX);

	int height = baseLine + (int)(normalized * (double)variation);

	return clampInt(height, 1, worldHeightValue - 2);

}

int FlatProfile::classifyBiome(int height)
{
	if (height < seaLevelValue) {

		return Biome::AQUATIC;

	}

	if (height >= 30) {
		return Biome::AERIAL;
	}

	return Biome::PLAINS;

}



int FlatProfile::getSeaLevel()
{
	return seaLevelValue;
}

int FlatProfile::getWorldHeight()
{
	return worldHeightValue;
}

const char* FlatProfile::getName()
{
	return "FLAT";
}

