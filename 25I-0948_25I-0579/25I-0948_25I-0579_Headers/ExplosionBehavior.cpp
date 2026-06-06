#include "ExplosionBehavior.h"
#include "EntityManager.h"
#include "FirePool.h"
#include <iostream>
#include"ExplosionVisual.h"
#include"ScoreManager.h"


ExplosionBehavior::ExplosionBehavior(float radius, float damage, bool fire,float fireDur):
	blastRadius(radius), blastDamage(damage), spawnsFire(fire), fireDuration(fireDur){ }

void ExplosionBehavior::explode(float cx, float cy, EntityManager& entityManager) {
	//cx and cy are the world space center of the explosion

	// this spawns the visual effect of the fire
	entityManager.add(new ExplosionVisual(cx, cy, blastRadius));

	int kills = entityManager.applyExplosionDamage(cx, cy, blastRadius, blastDamage);
	
	// add multiple kills score
	if (kills == 2) {
		ScoreManager::recordFlawlessVictory();
		ScoreManager::addScore(200);

	}

	// add massacre score
	else if (kills >= 3) ScoreManager::addScore(300 + (kills - 3) * 50);


	if (spawnsFire) {
		//for only FireBombGrenade and Iron Nokana boss spawn fire is true
		//for these, creating a pointer to the firepool and adding it to the 
		//entity manager which will own it and update, render etc it.

		FirePool* fireP = new FirePool(cx, cy, blastRadius, 2.0f, fireDuration);

		entityManager.add(fireP);

	}

	//for checking
	std::cout << "explosion centre = ( " << cx << ", " << cy << ", " << " )"<<endl;

}
//also destroys blocks in radius

float ExplosionBehavior::getRadius() const { return blastRadius; }
float ExplosionBehavior::getDamage() const { return blastDamage; }
float ExplosionBehavior::doesSpawnFire()const { return spawnsFire; }
float ExplosionBehavior::getFireDur() const { return fireDuration; }

