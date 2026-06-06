#pragma once
#include"AerialVehicle.h"
#include"Weapon.h"
#include"HeavyMachineGun.h"
#include"RocketLauncher.h"

class SlugFlyer : public AerialVehicle
{
private:
	Weapon* bulletFire;
	Weapon* rocketLauncher;
public:
	SlugFlyer(float startX, float startY);
	void move(float dirX, float dirY, float passedTime) override;
	void attack()override;
	void secondaryAttack()override;
	void setProjectileManager(ProjectileManager* pm);
};


