#pragma once
#include"GroundEnemy.h"

class ShieldedSoldier : public GroundEnemy
{
public:
	ShieldedSoldier(float startX, float startY, PlayerSoldier* player);
	void takeDamage(int amount, bool meleeAttack = false)override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper);
};

