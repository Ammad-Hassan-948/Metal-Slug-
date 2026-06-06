#pragma once
#include"AirEnemy.h"

class FlyingTara : public AirEnemy
{
public:
	FlyingTara(float startX, float startY, PlayerSoldier* player);
	void update(float passedTime)override;
	void fireWeapon()override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
};


