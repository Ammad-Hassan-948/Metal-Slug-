#pragma once
#include"AirEnemy.h"
#include"PlayerSoldier.h"

class MartianAir : public AirEnemy
{
public:
	MartianAir(float startX, float startY, PlayerSoldier* player);
	void update(float passedTime)override;
	void die()override;
	void fireWeapon()override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
};


