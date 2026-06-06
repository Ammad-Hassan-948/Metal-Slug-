#pragma once
#include "GameConstants.h"

class InterfaceWorld;

static const int MAX_CRATERS = 20;

struct CraterRecord {

	int centerX; //world block X
	 
	int centerY; //world block Y

	int radius; //radius in blocks

	float wetTime; //seconds of rain exposure accumulated so far

	bool active; // false for slot being free to reuse
	 
	bool filled;  //true once water is filled


};


class Environment {

public:

	Environment(unsigned int seed);


	void update(float dt, InterfaceWorld* world);


	void registerCrater(int centerBlockX, int centerBlockY, int radiusBlocks);


	bool isRaining() const;

private:

	bool raining;

	float phaseTimer; 

	unsigned int lcg;

	unsigned int lcgNext();

	CraterRecord craters[MAX_CRATERS];


	float randomDuration(float minSec, float maxSec);

	void fillCrater(CraterRecord& craterRecord, InterfaceWorld* world);

};