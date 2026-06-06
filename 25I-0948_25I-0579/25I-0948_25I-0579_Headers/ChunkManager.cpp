#include "ChunkManager.h"
#include"INoiseProfile.h"
#include"GameConstants.h"

ChunkManager::ChunkManager()
{
	for (int i = 0; i < CampaignConstants::MAX_LOADED_CHUNKS; i++) {

		slots[i] = nullptr; indices[i] = EMPTY;
	}
}

ChunkManager::~ChunkManager()
{
	for (int i = 0; i < CampaignConstants::MAX_LOADED_CHUNKS; i++) {
		if (slots[i] != nullptr) {
			delete slots[i];
			slots[i] = nullptr;
		}
		
	}
}

void ChunkManager::update(float playerWorldPixelX, INoiseProfile* profile)
{

	//converting pixelX to blockX and then to chunk index

	int playerBlockX = (int)(playerWorldPixelX / CampaignConstants::CELL_SIZE);

	int playerChunk = worldXToChunkIndex(playerBlockX);

	int rangeMin = playerChunk - CampaignConstants::VIEW_RADIUS;

	int rangeMax = playerChunk + CampaignConstants::VIEW_RADIUS;

	for (int i = 0; i < CampaignConstants::MAX_LOADED_CHUNKS; i++) {

		if (indices[i] == EMPTY)continue;

		if (indices[i] < rangeMin || indices[i] > rangeMax) {
			freeSlot(i);

		}
	}


	for (int colIndex = rangeMin; colIndex <= rangeMax; colIndex++) {
		if (findSlot(colIndex) == -1) {

			loadChunk(colIndex, profile);//generating a chunk at an missing chunk index
		}
	}
}

Block ChunkManager::getBlock(int worldX, int y) const
{
	int colIndex = worldXToChunkIndex(worldX);

	int slot = findSlot(colIndex);

	if (slot == -1) {
		return Block();
	}

	return slots[slot]->getBlock(worldX, y);
}

void ChunkManager::setBlock(int worldX, int y, int blockType)
{
	

	int colIndex = worldXToChunkIndex(worldX);

	int slot = findSlot(colIndex);

	if (slot == -1) {

		return;
	}

	slots[slot]->getBlock(worldX, y).type = blockType;

	slots[slot]->dirty = true;
}

bool ChunkManager::isSolid(int worldX, int y) const
{
	int t = getBlock(worldX, y).type;

	return (t != BlockType::AIR && t != BlockType::WATER);
}

bool ChunkManager::isWater(int worldX, int y) const
{
	return getBlock(worldX, y).type == BlockType::WATER;
}

int ChunkManager::worldXToChunkIndex(int worldX)
{
	
	if (worldX >= 0) {

		return worldX / CampaignConstants::CHUNK_WIDTH;
	}

	return -((-worldX + CampaignConstants::CHUNK_WIDTH - 1) / CampaignConstants::CHUNK_WIDTH);
}

int ChunkManager::findSlot(int chunkI) const
{
	
	for (int i = 0; i < CampaignConstants::MAX_LOADED_CHUNKS; i++) {

		if (indices[i] == chunkI) {
			return i;
		}
		
	}

	return -1;
}

int ChunkManager::findFreeSlot() const
{
	for (int i = 0; i < CampaignConstants::MAX_LOADED_CHUNKS; i++) {

		if (indices[i] == EMPTY) {

			return i;
		}
	}

	return -1;
}

void ChunkManager::loadFreeSlot() const
{


}

void ChunkManager::loadChunk(int chunkIndex, INoiseProfile* profile)
{

	int slot = findFreeSlot();

	if (slot == -1) {

		return;
	}

	Chunk* c = new Chunk();

	c->chunkIndex = chunkIndex;
	c->generate(profile);



	slots[slot] = c;
	indices[slot] = chunkIndex;


}

void ChunkManager::freeSlot(int slot)
{
	delete slots[slot];
	slots[slot] = nullptr;

	indices[slot] = EMPTY;
}

