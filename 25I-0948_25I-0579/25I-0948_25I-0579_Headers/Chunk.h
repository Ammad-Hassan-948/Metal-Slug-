#pragma once
#include "Block.h"
#include"GameConstants.h"


class INoiseProfile;

//chunk is a fixed width vertical strip of the world
//only the chunks near the player, keeping those in memory only

//each hcunk will be 32 in width and 60 blocks in height
//using chunk index for tracking where this chunk would sit and where in the world


class Chunk {

public:

	Block data[CampaignConstants::CHUNK_WIDTH][CampaignConstants::WORLD_HEIGHT];

	int chunkIndex; //positionm in the infinite world
	
	bool dirty; //if any block was modified after generation

	Chunk();


	void generate(INoiseProfile* profile);//fill data based on the profile*


	Block& getBlock(int worldX, int y); //to access a block by worldX coordinate; return ref to edit


	const Block& getBlock(int worldX, int y) const; //read only

private:

	int determineBlockType(int y, int surfaceY, int biome, int seaLevel) const;

};