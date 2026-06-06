#pragma once
#include"GroundEnemy.h"

class M15ABradley : public GroundEnemy
{
public:
	M15ABradley(float startX, float startY, PlayerSoldier* player);
	void fireWeapon()override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
};


