#include "CampaignWorld.h"
#include "ProfileFactory.h"
#include "GameConstants.h"
#include <cmath>

CampaignWorld::CampaignWorld(int profileKind, unsigned int seed):profile(ProfileFactory::create(profileKind, seed)), 
environment(seed + 1u), spawner(seed + 2u)
{
}

CampaignWorld::~CampaignWorld()
{
	delete profile; profile = nullptr;
}

void CampaignWorld::update(float dt, float playerWorldPixelX)
{
	chunkManager.update(playerWorldPixelX, profile);//to ensure terrain is loaded in memory

	environment.update(dt, this); //to write blocks where required

	spawner.update(dt, playerWorldPixelX, //queries getbiome and getsurfaceY
		this);
}

int CampaignWorld::getBlockType(int worldX, int worldY)
{
	return chunkManager.getBlock(worldX, worldY).type;
}

void CampaignWorld::setBlockType(int worldX, int worldY, int blockType)
{
	return chunkManager.setBlock(worldX, worldY, blockType);
}

bool CampaignWorld::isSolid(int worldX, int worldY)
{
	return chunkManager.isSolid(worldX, worldY);
}

bool CampaignWorld::isWater(int worldX, int worldY)
{
	return chunkManager.isWater(worldX, worldY);
}

int CampaignWorld::getWorldHeight()
{
	return CampaignConstants::WORLD_HEIGHT;
}

int CampaignWorld::getSeaLevel()
{
	return profile->getSeaLevel();
}

int CampaignWorld::getBiomeAt(int worldX)
{
	int h = profile->getHeightAt(worldX);

	return profile->classifyBiome(h);

}



int CampaignWorld::getSurfaceY(int worldX)
{

	return profile->getHeightAt(worldX);
}



void CampaignWorld::applyExplosion(float cx, float cy, float radius)
{

	const int blockSize = CampaignConstants::BLOCK_SIZE_PIXELS;

	const int worldHeight = CampaignConstants::WORLD_HEIGHT;

	int centerBlockX = (int)(cx / (float)blockSize);


	//changing the pixel center to block coordinates


	int centerScreenRow =
		(int)(cy / (float)blockSize);


	int centerY_bottom = worldHeight - 1 - centerScreenRow;


	int radiusBlocks =
		(int)(radius / (float)blockSize) + 1;


	for (int dx = -radiusBlocks; dx <= radiusBlocks; dx++) {

		for (int dy = -radiusBlocks; dy <= radiusBlocks; dy++) {


			if (dx * dx + dy * dy > radiusBlocks * radiusBlocks) { continue; }
			//skipping if the block is outside the blast radius

			int widthX = centerBlockX + dx;

			int widthY = centerY_bottom + dy; // y frpm bottom


			if (widthY < 0 || widthY >= worldHeight) { continue; }

			int blockType = getBlockType(widthX, widthY);

			if (blockType == BlockType::BEDROCK || blockType == BlockType::AIR)continue;


			setBlockType(widthX, widthY, BlockType::AIR);
		}
	}


	environment.registerCrater(centerBlockX, centerY_bottom, radiusBlocks);

}

bool CampaignWorld::hasSpawnRequest() const
{
	return spawner.hasSpawnRequest();
}


void CampaignWorld::consumeSpawnRequest(float& outX, float& outY, int& outType)
{

	spawner.consumeSpawnRequest(outX, outY, outType);
}

void CampaignWorld::onEnemyKilled(int typeId)
{
	spawner.onEnemyKilled(typeId);

}

void CampaignWorld::onVehicleDestroyed(int typeId)
{
	spawner.onVehicleDestroyed(typeId);
}

bool CampaignWorld::isObjectiveComplete() const
{
	return spawner.isObjectiveComplete();
}

bool CampaignWorld::isRaining() const
{
	return environment.isRaining();
}

int CampaignWorld::getEnemyKillCount(int typeId) const
{
	return spawner.getEnemyKillCount
		(typeId);
}



int CampaignWorld::getVehicleKillCount(int typeId) const
{
	return spawner.getVehicleKillCount(typeId);
}
