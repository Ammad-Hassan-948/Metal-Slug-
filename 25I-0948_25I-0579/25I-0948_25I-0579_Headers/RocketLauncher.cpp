#include "RocketLauncher.h"
#include"DamagableEntity.h"
#include"ProjectileManager.h"

RocketLauncher::RocketLauncher(int ammo) : Weapon(ammo, 600.0f, 5, 0.5f, "Rocket Launcher") { }

Projectile* RocketLauncher::fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)
{
	if (ammoAvailable() && projMgr != nullptr) {

		int shooterType = shooter->getHitbox().getType();
		int type = (shooterType == ColliderType::Player || shooterType == ColliderType::Vehicle) ? 
			ColliderType::PlayerBullet : ColliderType::EnemyBullet;
		
		projMgr->spawnRocket(startX, startY, angle, type);
		
	}

	return nullptr;
}

