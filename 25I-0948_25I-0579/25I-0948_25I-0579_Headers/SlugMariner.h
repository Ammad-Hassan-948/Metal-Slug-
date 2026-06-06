#pragma once
#include"AquaticVehicle.h"
#include"RocketLauncher.h"
class SlugMariner : public AquaticVehicle
{
public:
	Weapon* rocketLauncher;
	Weapon* bulletFire;
	int horizontal;
	int vertical;
	int projectile;
	SlugMariner(float startX, float startY);
	void setProjectileManager(ProjectileManager* pm);
private:
	void move(float dirX, float dirY, float passedTime) override;
	void attack()override;
	void secondaryAttack()override;
	
};


