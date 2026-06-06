#pragma once
#include"Weapon.h"

class LaserGun : public Weapon
{
public:
	LaserGun(int ammo);
	Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter = nullptr)override;
};

