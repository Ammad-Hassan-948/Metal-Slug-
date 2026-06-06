#include "DamagableEntity.h"
#include "ProjectileManager.h"
#include"Projectile.h"
#include"FlameShotGun.h"

FlameShotGun::FlameShotGun(int ammo) : Weapon(ammo, 300.0f, 2, 10.0f, "Flame Shotgun") {}

Projectile* FlameShotGun::fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)
{
	if (ammoAvailable() && projMgr != nullptr) {
		int shooterType = shooter->getHitbox().getType();
		int type = (shooterType == ColliderType::Player || shooterType == ColliderType::Vehicle) ? 
			ColliderType::PlayerBullet : ColliderType::EnemyBullet;

		projMgr->spawnFlame(startX, startY, angle, type);
	}

	return nullptr;
}

