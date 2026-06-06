#include "CampaignEnemySpawner.h"
#include "InterfaceWorld.h"
#include "GameConstants.h"

static const float SCREEN_HALFW_PIXELS = 800.0f;

CampaignEnemySpawner::CampaignEnemySpawner(unsigned int seed):spawnTimer(2.5f), lcg(seed),
pendingSpawn(false), pendingX(0.0f), pendingY(0.0f), pendingType(0)
{
	for (int i = 0; i < EnemyType::COUNT; i++) {
		enemyKills[i] = 0;
	}

	for (int i = 0; i < VehicleType::COUNT; i++) {
		vehicleKills[i] = 0;
	}
}

void CampaignEnemySpawner::update(float dt, float playerWorldPixelX, InterfaceWorld* world)
{

	pendingSpawn = false;

	spawnTimer -= dt;

	if (spawnTimer > 0.0f || world == nullptr) {
		return;
	}

	spawnTimer = 2.0f + (float)(randomInt(100)) * 0.01f;

	float side = (randomInt(2) == 0) ? -1.0f : 1.0f;

	float offset = SCREEN_HALFW_PIXELS + (float)CampaignConstants::BLOCK_SIZE_PIXELS +
		(float)(randomInt(6) * CampaignConstants::BLOCK_SIZE_PIXELS);

	float spawnPixelX = playerWorldPixelX + side * offset;

	int blockX = (int)(spawnPixelX / (float)CampaignConstants::BLOCK_SIZE_PIXELS);

	int biome = world->getBiomeAt(blockX);


	int surfaceY = world->getSurfaceY(blockX);

	int screenRow = world->getWorldHeight() - 1 - surfaceY;

	float spawnPixelY = (float)(screenRow - 2) * (float)CampaignConstants::BLOCK_SIZE_PIXELS;

	int eType = pickEnemyType(biome);

	pendingSpawn = true;

	pendingX = spawnPixelX;

	pendingY = spawnPixelY;

	pendingType = eType;

}

bool CampaignEnemySpawner::hasSpawnRequest() const
{
	return pendingSpawn;
}

void CampaignEnemySpawner::consumeSpawnRequest(float& outPixelX, float& outPixelY, int& outEnemyType)
{

	outPixelX = pendingX;

	outPixelY = pendingY;

	outEnemyType = pendingType;

	pendingSpawn = false;

}

void CampaignEnemySpawner::onEnemyKilled(int enemyTypeId)
{

	if (enemyTypeId >= 0 && enemyTypeId < EnemyType::COUNT) {

		enemyKills[enemyTypeId]++;
	}
}

void CampaignEnemySpawner::onVehicleDestroyed(int vehicleTypeId)
{


	if (vehicleTypeId >= 0 && vehicleTypeId < VehicleType::COUNT) {

		vehicleKills[vehicleTypeId]++;
	}
}

bool CampaignEnemySpawner::isObjectiveComplete() const
{
	for (int i = 0; i < EnemyType::COUNT; i++) {
		if (i == EnemyType::IRON_NOKANA) continue;
		if (enemyKills[i] < CampaignConstants::ENEMY_KILL_QUOTA) {
			return false;
		}
	}
	return true;
}

int CampaignEnemySpawner::getEnemyKillCount(int typeId) const
{
	if (typeId < 0 || typeId >= EnemyType::COUNT) {
		return 0;
	}

	return enemyKills[typeId];
}

int CampaignEnemySpawner::getVehicleKillCount(int typeId) const
{
	if (typeId < 0 || typeId >= VehicleType::COUNT) {
		return 0;
	}

	return vehicleKills[typeId];
}




unsigned int CampaignEnemySpawner::lcgNext()
{
	lcg = lcg * 1664525u + 1013904223u;

	return lcg;
}




int CampaignEnemySpawner::randomInt(int maxExclusive)
{
	if (maxExclusive <= 0) { return 0; }

	return (int)(lcgNext() % (unsigned int)maxExclusive);
}

int CampaignEnemySpawner::pickEnemyType(int biome)
{
	if (biome == Biome::AERIAL) {

		int choice = randomInt(3);
		if (choice == 0) return EnemyType::MARTIAN;
		if (choice == 1) return EnemyType::FLYING_TARA;
		return EnemyType::PARATROOPER;
	}


	if (biome == Biome::AQUATIC) {

		return (randomInt(2) == 0) ? EnemyType::ZOMBIE : EnemyType::ENEMY_SUB;
	}

	int choice = randomInt(6);

	if (choice == 0) return EnemyType::REBEL_SOLDIER;

	if (choice == 1) return EnemyType::BAZOOKA_SOLDIER;

	if (choice == 2) return EnemyType::GRENADE_SOLDIER;

	if (choice == 3) return EnemyType::MUMMY;

	if (choice == 4) return EnemyType::SHIELDED_SOLDIER;

	return EnemyType::M15A_BRADLEY;
}
