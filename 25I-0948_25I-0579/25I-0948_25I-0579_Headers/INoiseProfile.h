#pragma once

//abstract class to track surface height at col X, biome at that height and total height 
// for each terrain profile


class INoiseProfile {

public:


	virtual ~INoiseProfile(){}


	virtual int getHeightAt(int worldX) = 0;// y= 0 bedrock, y = height - 1 is the sky

	virtual int classifyBiome(int height) = 0;//return biome according to height thresold

	virtual int getSeaLevel() = 0;// y coordinate from bottom below which cols are filled with water


	virtual int getWorldHeight() = 0;//total block rows inthe world


	virtual const char* getName() = 0;
};