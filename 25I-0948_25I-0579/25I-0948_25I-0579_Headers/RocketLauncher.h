#pragma once
#include"Weapon.h"

class RocketLauncher : public Weapon
{
public:
	RocketLauncher(int ammo);
	Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)override;
};

