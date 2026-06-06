#pragma once


class Projectile;

class Soldier;

class DamagableEntity;

class ProjectileManager;

class Weapon
{
protected:
	int ammo;
	float projectileSpeed;
	int damage;
	float fireRate;
	const char* name;
	// also keep a manager for projectiles
	ProjectileManager* projMgr;
public:
	Weapon(int ammo, float projectileSpeed, int damage, float fireRate, const char* name);
	virtual ~Weapon() = default;
	int getAmmo()const;
	float getFireRate()const;
	const char* getName()const;
	void setProjectileManager(ProjectileManager* p);
	void addAmmo(int a);
	bool ammoAvailable();
	bool weaponEmpty()const;
	virtual Projectile* fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter = nullptr) = 0;
};

