#pragma once
#include"GroundEnemy.h"

class MummyWarrior : public GroundEnemy
{
private:
	bool hasCrumbled;
	float resurrectionTimer;
public:
	MummyWarrior(float startX, float startY, PlayerSoldier* player);
	// override function on how to fire as mummy does not fire
	void fireWeapon()override;
	void takeDamage(int amount, bool meleeAttack = false)override;
	void update(float passedTime)override;
	static void spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm);
};

