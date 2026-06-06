#include "GrenadeWeapon.h"
#include "DamagableEntity.h"
#include "ProjectileManager.h"

GrenadeWeapon::GrenadeWeapon(int ammo) : Weapon(ammo, 400.0f, 20, 0.5f, "Grenades") {}

Projectile* GrenadeWeapon::fire(float startX, float startY, int direction, float angle, DamagableEntity* shooter)
{
	if (ammoAvailable() && projMgr != nullptr) {
		int shooterType = shooter->getHitbox().getType();
		int type = (shooterType == ColliderType::Player || shooterType == ColliderType::Vehicle) ? 
			ColliderType::PlayerBullet : ColliderType::EnemyBullet;

		float vx = (direction == 1) ? 300.0f : -300.0f;
		float vy = -500.0f; // Upward toss

		projMgr->spawnHandGrenade(startX, startY, vx, vy, type);
	}

	return nullptr;
}


