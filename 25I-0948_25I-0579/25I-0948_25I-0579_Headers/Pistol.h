#pragma once
#include"Weapon.h"

class Pistol : public Weapon
{
public:
	Pistol(int ammo);
	Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)override;
};

