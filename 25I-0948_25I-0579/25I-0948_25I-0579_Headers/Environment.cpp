#include "Environment.h"
#include "InterfaceWorld.h"
#include "GameConstants.h"

static const float CRATER_FILL_SECONDS = 3.0f;
static const float RAIN_MIN_SECONDS = 15.0f;
static const float RAIN_MAX_SECONDS = 45.0f;
static const float DRY_MIN_SECONDS = 30.0f;
static const float DRY_MAX_SECONDS = 90.0f;



Environment::Environment(unsigned int seed) :raining(false), phaseTimer(0.0f), lcg(seed) {

	phaseTimer = randomDuration(DRY_MIN_SECONDS, DRY_MAX_SECONDS);

	for (int i = 0; i < MAX_CRATERS; i++) {

		craters[i].active = false;
		craters[i].filled = false;

		craters[i].wetTime = 0.0f;

		craters[i].centerX = 0;

		craters[i].centerY = 0;

		craters[i].radius = 0;
	}
}


void Environment::update(float dt, InterfaceWorld* world)
{


	phaseTimer -= dt;

	if (phaseTimer <= 0.0f) {

		raining = !raining;

		phaseTimer = raining ?
			randomDuration(RAIN_MIN_SECONDS, RAIN_MAX_SECONDS) : randomDuration(DRY_MIN_SECONDS,
				DRY_MAX_SECONDS);
	}


	if (!raining || world == nullptr)return;


	for (int i = 0; i < MAX_CRATERS; i++) {

		if (!craters[i].active || craters[i].filled) { continue; }

		craters[i].wetTime += dt;

		//crater flooding
		if (craters[i].wetTime >= CRATER_FILL_SECONDS)
		{
			fillCrater(craters[i], world);

			craters[i].filled = true;
			craters[i].active = false;
		}
	}
}

void Environment::registerCrater(int centerBlockX, int centerBlockY, int radiusBlocks)
{

	if (radiusBlocks != 1)return;


	for (int i = 0; i < MAX_CRATERS; i++) {

		if (!craters[i].active) {

			craters[i].centerX = centerBlockX;

			craters[i].centerY = centerBlockY;
			
			craters[i].radius = radiusBlocks;

			craters[i].wetTime = 0.0;

			craters[i].filled = false;

			craters[i].active = true; return;
		}
	}
}

void Environment::fillCrater(CraterRecord& craterRecord, InterfaceWorld* world)
{
	for (int dX = -craterRecord.radius; dX <= craterRecord.radius; dX++) {

		int widthX = craterRecord.centerX + dX;


		for (int dy = -craterRecord.radius; dy <= 0; dy++) {

			int widthY = craterRecord.centerX + dy;

			if (widthY < 1) {
				continue;
			}

			if (world->getBlockType(widthX, widthY) == BlockType::AIR) {
				world->setBlockType(widthX, widthY, BlockType::WATER);
			}

		}
	}
}


bool Environment::isRaining() const
{
	return raining;
}

unsigned int Environment::lcgNext()
{
	lcg = lcg * 1664525u + 1013904223u;
	return lcg;
}

float Environment::randomDuration(float minSec, float maxSec)
{
	unsigned int range = (unsigned int)(maxSec - minSec);

	if (range == 0)return minSec;

	return minSec + (float)(lcgNext() % (range + 1u));
}


