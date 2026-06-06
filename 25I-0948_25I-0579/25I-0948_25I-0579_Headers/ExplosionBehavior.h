#pragma once
#include "EntityManager.h"
#include"LevelManager.h"

class ExplosionBehavior {
private:
	float blastRadius;
	float blastDamage;
	bool spawnsFire;
	float fireDuration;

public:
	ExplosionBehavior(float radius, float damage, bool spawnsFire = false, float fireDuration = 0.0f);

	void explode(float x, float y, EntityManager& entityManager);
	//also destroys blocks in radius


	float getRadius() const;
	float getDamage() const;
	float doesSpawnFire()const;
	float getFireDur() const;
};
