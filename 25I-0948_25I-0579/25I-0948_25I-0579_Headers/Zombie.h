#pragma once
#include"GroundEnemy.h"

class Zombie : public GroundEnemy
{
public:
	Zombie(float startX, float startY, PlayerSoldier* player);
	void update(float passedTime)override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
};

