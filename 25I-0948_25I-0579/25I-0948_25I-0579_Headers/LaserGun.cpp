#include "LaserGun.h"
#include "DamagableEntity.h"
#include "ProjectileManager.h"

LaserGun::LaserGun(int ammo) : Weapon(ammo, 1500.0f, 100, 2.0f, "Laser Gun") {}

Projectile* LaserGun::fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)
{
	if (ammoAvailable() && projMgr != nullptr) {
		int shooterType = shooter->getHitbox().getType();
		int type = (shooterType == ColliderType::Player || shooterType == ColliderType::Vehicle) ? 
			ColliderType::PlayerBullet : ColliderType::EnemyBullet;

		projMgr->spawnLaser(startX, startY, angle, type);
	}

	return nullptr;
}
