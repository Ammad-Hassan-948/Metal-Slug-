#include "Boss.h"
#include "EntityManager.h"
#include "SupplyCrate.h"
#include"ScoreManager.h"

Boss::Boss(float x, float y, int hp, const char* name, PlayerSoldier* player, EntityManager* mgr, 
	ProjectileManager* pMgr) :
	Enemy(x, y, 0.0f, 0.0f, 0.0f, 256.0f, 256.0f, 0.0f, 0.0f, 1, hp, name, player) {
	this->EntityMgr = mgr;
	this->projectileManager = pMgr;
	this->maxHp = hp;
	this->hasRetreated = false;
	this->retreatTriggered = false;
	this->minionsSpawnedInBatch = 0;
	this->minionsKilledInBatch = 0;
	this->aloneBoss = true;
}


void Boss::takeDamage(int amount, bool meleeAttack) {

	if (retreatTriggered) {
		return;
	}

	Enemy::takeDamage(amount);
	//retreating if hp drops to less than 50
	if (hp <= (maxHp / 2) && aloneBoss) {

		retreatTriggered = true;
		ScoreManager::addScore(500);
		retreat();
	}
}

void Boss::notifyMinionDeath() {
	minionsKilledInBatch++;
	if (minionsKilledInBatch >= minionsSpawnedInBatch && minionsSpawnedInBatch > 0) {
		
		std::cout << "spawning supply crate." << std::endl;
		
		EntityMgr->add(new SupplyCrate(positionX, positionY));

		minionsKilledInBatch = 0;
		minionsSpawnedInBatch = 0;
	}

}