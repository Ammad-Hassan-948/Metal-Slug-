#pragma once
#include"Weapon.h"

class HeavyMachineGun : public Weapon
{
public:
	HeavyMachineGun(int ammo);
	Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)override;
};

