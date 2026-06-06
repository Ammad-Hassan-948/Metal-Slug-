#pragma once
#include"GroundEnemy.h"

class RebelSoldier : public GroundEnemy
{
public:
	RebelSoldier(float startX, float startY, PlayerSoldier* player);
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper);
};

