#pragma once
class InterfaceWorld {

public:
	virtual ~InterfaceWorld() {}

	virtual int getBlockType(int worldX, int worldY) = 0;

	virtual void setBlockType(int worldX, int worldY, int blockType) = 0;

	virtual bool isSolid(int worldX, int worldY) = 0;

	virtual int getWorldHeight() = 0;

	virtual int getSeaLevel() = 0;


	virtual int getBiomeAt(int worldX) = 0;

	virtual int getSurfaceY(int worldX) = 0;


	virtual void applyExplosion(float cx, float cy, float radius) = 0;
};