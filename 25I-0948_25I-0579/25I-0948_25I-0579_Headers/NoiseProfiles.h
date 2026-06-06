#pragma once
#include "INoiseProfile.h"

#include "FractalNoise.h"


//normal profile has moderate peaks and ocean

class NormalProfile :public INoiseProfile {

	FractalNoise noise;

	int baseLine;

	int variation;

	int seaLevelValue; int worldHeightValue;

public:

	NormalProfile(unsigned int seed);

	int getHeightAt(int worldX) override;

	int classifyBiome(int height) override;

	int getSeaLevel() override;

	int getWorldHeight() override;

	const char* getName() override;
};


class AmplifiedProfile :public INoiseProfile {

	FractalNoise noise;

	int baseLine;

	int variation;

	int seaLevelValue; int worldHeightValue;

public:

	AmplifiedProfile(unsigned int seed);

	int getHeightAt(int worldX) override;

	int classifyBiome(int height) override;

	int getSeaLevel() override;

	int getWorldHeight() override;

	const char* getName() override;
};


class FlatProfile :public INoiseProfile {

	FractalNoise noise;

	int baseLine;

	int variation;

	int seaLevelValue; int worldHeightValue;

public:

	FlatProfile(unsigned int seed);

	int getHeightAt(int worldX) override;

	int classifyBiome(int height) override;

	int getSeaLevel() override;

	int getWorldHeight() override;

	const char* getName() override;
};