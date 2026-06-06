#pragma once
#include"Collectibles.h"

class PowPrisoner : public Collectibles
{
public:
	PowPrisoner(float posX, float posY);
	void interact(PlayerSoldier* p)override;
	void applyEffect(PlayerSoldier* p)override;
	bool needsInput()const override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr);
	void update(float passedTime)override;
};


