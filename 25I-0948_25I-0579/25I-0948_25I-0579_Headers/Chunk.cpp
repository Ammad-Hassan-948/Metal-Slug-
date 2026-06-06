#include "Chunk.h"
#include "INoiseProfile.h"
#include "GameConstants.h"


Chunk::Chunk():chunkIndex(0), dirty(false)
{
}

void Chunk::generate(INoiseProfile* profile)
{
	int worldHeight = CampaignConstants::WORLD_HEIGHT;

	int seaLevel = profile->getSeaLevel();

	for (int localX = 0; localX < CampaignConstants::CHUNK_WIDTH; localX++) {

		//converting localX to the worldX in the infnite world col

		int worldX = chunkIndex * CampaignConstants::CHUNK_WIDTH + localX;

		//height of the terrain at that X
		int surfaceY = profile->getHeightAt(worldX);


		//biome at that surface
		int biome = profile->classifyBiome(surfaceY);
	
		for (int y = 0; y < worldHeight; y++) {

			int bType = determineBlockType(y, surfaceY, biome, seaLevel);

			int hp = 0;

			if (bType != BlockType::AIR && bType != BlockType::WATER && bType != BlockType::BEDROCK) {

				hp = 3;//all others can take 3 hits but not air, water or bedrock
			}

			data[localX][y] = Block(bType, hp, false);
		}
	}

	dirty = false;
}




Block& Chunk::getBlock(int worldX, int y)
{
	int localX = worldX - chunkIndex * CampaignConstants::CHUNK_WIDTH;

	return data[localX][y];
}



const Block& Chunk::getBlock(int worldX, int y) const
{
	int localX = worldX - chunkIndex * CampaignConstants::CHUNK_WIDTH;
	return data[localX][y];
}




int Chunk::determineBlockType(int y, int surfaceY, int biome, int seaLevel) const
{
	if (y == 0) { return BlockType::BEDROCK; }


	if (y > surfaceY) {

		if (biome == Biome::AQUATIC && y <= seaLevel) {

			return BlockType::WATER;
		}

		return BlockType::AIR;
	}


	if (y == surfaceY) {

		if (biome == Biome::AQUATIC) { return BlockType::SAND; }

		if (biome == Biome::AERIAL) {
			return BlockType::SNOW;
		}


		return BlockType::GRASS;
	}


	int depthFromSurface = surfaceY - y; if (depthFromSurface <= 3) {
		return BlockType::DIRT;
	}

	return BlockType::STONE;
}


