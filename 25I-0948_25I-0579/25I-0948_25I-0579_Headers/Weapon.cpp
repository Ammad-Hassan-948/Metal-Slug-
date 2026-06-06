#include "Weapon.h"
#include"DamagableEntity.h"
#include"ProjectileManager.h"

Weapon::Weapon(int ammo, float projectileSpeed, int damage, float fireRate, const char* name): 
	ammo(ammo), projectileSpeed(projectileSpeed), damage(damage), fireRate(fireRate), name(name) { }

int Weapon::getAmmo() const
{
	return ammo;
}

float Weapon::getFireRate() const
{
	return fireRate;
}

const char* Weapon::getName() const
{
	return name;
}

void Weapon::setProjectileManager(ProjectileManager* p)
{
	projMgr = p;
}

void Weapon::addAmmo(int a)
{
	ammo += a;
}

bool Weapon::ammoAvailable()
{
	// for infinite ammo pistol
	if (ammo == -1)
		return true;

	// if ammo has ended
	if (ammo <= 0)
		return false;

	// this means we have ammo still
	ammo--;

	return true;
}

bool Weapon::weaponEmpty()const
{
	// if it is a pistol it never gets empty
	if (ammo == -1)
		return false;

	if (ammo <= 0)
		return true;

	return false;
}

