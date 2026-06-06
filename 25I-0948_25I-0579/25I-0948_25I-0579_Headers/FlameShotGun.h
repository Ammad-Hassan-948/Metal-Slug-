#pragma once
#include"Weapon.h"

class Projectile;

class FlameShotGun : public Weapon
{
public:
	FlameShotGun(int ammo);
	Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter = nullptr)override;
};

