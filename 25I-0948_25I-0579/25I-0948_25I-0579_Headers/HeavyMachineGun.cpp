#include "HeavyMachineGun.h"
#include "DamagableEntity.h"
#include "ProjectileManager.h"

HeavyMachineGun::HeavyMachineGun(int ammo) : Weapon(ammo, 1000.0f, 3, 8, "Heavy Machine Gun") {}

Projectile* HeavyMachineGun::fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)
{
	if (ammoAvailable() && projMgr != nullptr) {
		int shooterType = shooter->getHitbox().getType();
		int type = (shooterType == ColliderType::Player || shooterType == ColliderType::Vehicle) ? 
			ColliderType::PlayerBullet : ColliderType::EnemyBullet;

		projMgr->spawnBullet(startX, startY, angle, (float)damage, projectileSpeed, type);
	}

	return nullptr;
}

