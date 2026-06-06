#pragma once
#include"GroundEnemy.h"
class PlayerSoldier;

class GrenadeSoldier : public GroundEnemy
{
public:
	GrenadeSoldier(float startX, float startY, PlayerSoldier* player);
	void fireWeapon()override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper);
};

