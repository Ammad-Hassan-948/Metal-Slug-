#pragma once
#include "Enemy.h"

class EntityManager;

class ProjectileManager;

class Boss :public Enemy {

protected:

	bool hasRetreated;//to track if the boss has left the screen

	bool retreatTriggered;

	EntityManager* EntityMgr;

	int maxHp;

	ProjectileManager* projectileManager;

	int minionsSpawnedInBatch;
	int minionsKilledInBatch;

	bool aloneBoss;


		public:

	Boss(float x, float y, int hp, const char* name, PlayerSoldier* player, EntityManager* mgr,
	ProjectileManager* projectileManager);


	virtual void takeDamage(int amount, bool meleeAttack = false) override;

	virtual void spawnMinions() = 0;

	virtual void notifyMinionDeath();

	virtual void retreat() = 0;

	bool getHasRetreated() const {


		return hasRetreated;
	}

};