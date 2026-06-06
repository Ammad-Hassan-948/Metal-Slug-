#include "Pistol.h"
#include"DamagableEntity.h"
#include"ProjectileManager.h"

Pistol::Pistol(int ammo) : Weapon(ammo, 900.0f, 3, 4, "Pistol") { }

Projectile* Pistol::fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)
{
	if (ammoAvailable() && projMgr != nullptr) {

		int shooterType = shooter->getHitbox().getType();
		int type = (shooterType == ColliderType::Player || shooterType == ColliderType::Vehicle) ? 
			ColliderType::PlayerBullet : ColliderType::EnemyBullet;
			         
		projMgr->spawnBullet(startX, startY, angle, damage, projectileSpeed, type);
	
	}

	return nullptr;
}


