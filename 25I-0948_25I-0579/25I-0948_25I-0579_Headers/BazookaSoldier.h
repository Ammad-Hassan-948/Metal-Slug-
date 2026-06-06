#pragma once
#include"GroundEnemy.h"

class BazookaSoldier : public GroundEnemy
{
public:
	BazookaSoldier(float startX, float startY, PlayerSoldier* player);
	void fireWeapon()override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper);
};

