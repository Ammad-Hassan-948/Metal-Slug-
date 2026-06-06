#pragma once
#include "Chunk.h"
#include "GameConstants.h"


class ChunkManager {

public:
	static const int EMPTY = -99999;//just an indicator for empty slot

	ChunkManager();
	~ChunkManager();

	void update(float playerWorldPixelX, INoiseProfile* profile);
	//called every frame with players worldX and loads view within his view radius and removes ones out of radius


	Block getBlock(int worldX, int y) const;

	void setBlock(int worldX, int y, int blockType);


	bool isSolid(int worldX, int y) const;

	bool isWater(int worldX, int y) const;


private:

	Chunk* slots[CampaignConstants::MAX_LOADED_CHUNKS];
	int indices[CampaignConstants::MAX_LOADED_CHUNKS];


	static int worldXToChunkIndex(int worldX);

	int findSlot(int chunkI) const;


	int findFreeSlot() const;

	void loadFreeSlot() const;

	void loadChunk(int chunkIndex, INoiseProfile* profile);//load or generate a chunk to a free slot


	void freeSlot(int slot);

};