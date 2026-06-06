#pragma once
#include "InterfaceWorld.h"
#include "ChunkManager.h"
#include "Environment.h"
#include "CampaignEnemySpawner.h"


class CampaignWorld : public InterfaceWorld {


public:
	CampaignWorld(int profileKind, unsigned int seed);
	~CampaignWorld();

	void update(float dt, float playerWorldPixelX);

	int getBlockType(int worldX, int worldY) override;

	void setBlockType(int worldX, int worldY, int blockType) override;

	bool isSolid(int worldX, int worldY) override;


	bool isWater(int worldX, int worldY);

	int getWorldHeight() override;

	int getSeaLevel() override;

	int getBiomeAt(int worldX) override;

	int getSurfaceY(int worldX) override;

	void applyExplosion(float cx, float cy, float radius) override;


	bool hasSpawnRequest() const;

	void consumeSpawnRequest(float& outX, float& outY, int& outType);


	void onEnemyKilled(int typeId);

	void onVehicleDestroyed(int typeId);

	bool isObjectiveComplete() const;


	bool isRaining() const;

	int getEnemyKillCount(int typeId) const;

	int getVehicleKillCount(int typeId) const;

private:

	INoiseProfile* profile;

	ChunkManager chunkManager;

	Environment environment;

	CampaignEnemySpawner spawner;

};