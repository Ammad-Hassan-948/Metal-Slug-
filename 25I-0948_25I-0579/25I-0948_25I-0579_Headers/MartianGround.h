#pragma once
#include"GroundEnemy.h"

class MartianGround : public GroundEnemy
{
public:
	MartianGround(float startX, float startY, PlayerSoldier* player);
	void fireWeapon() override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
};

