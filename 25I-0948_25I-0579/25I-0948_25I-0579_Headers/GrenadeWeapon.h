#pragma once
#include"Weapon.h"

class GrenadeWeapon : public Weapon
{
public:
	GrenadeWeapon(int ammo);
	Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)override;
};

