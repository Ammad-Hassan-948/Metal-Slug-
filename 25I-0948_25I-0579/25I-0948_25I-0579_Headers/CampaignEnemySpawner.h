#pragma once
#include "GameConstants.h"


class InterfaceWorld;


class CampaignEnemySpawner {

public:

	CampaignEnemySpawner(unsigned int seed);


	void update(float dt, float playerWorldPixelX, InterfaceWorld* world);

	bool hasSpawnRequest() const;

	void consumeSpawnRequest(float& outPixelX, float& outPixelY, int& outEnemyType);

	void onEnemyKilled(int enemyTypeId);

	void onVehicleDestroyed(int vehicleTypeId);


	bool isObjectiveComplete() const;

	int getEnemyKillCount(int typeId) const;

	int getVehicleKillCount(int typeId) const;

private:

	float spawnTimer;

	unsigned int lcg;

	bool pendingSpawn;

	float pendingX;

	float pendingY;

	int pendingType;


	int enemyKills[EnemyType::COUNT];
	int vehicleKills[VehicleType::COUNT];


	unsigned int lcgNext();

	int randomInt(int maxExclusive);

	int pickEnemyType(int biome); 

};