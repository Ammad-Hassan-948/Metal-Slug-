#pragma once
#include "Boss.h"

class IronNokana : public Boss {

private:

	float missileTimer;
	float flamethrowerTimer;
	float minionsSpawnTimer;

	float fireBombTimer;

	int minionsKilled;
	


public:

	IronNokana(float x, float y, PlayerSoldier* player, EntityManager* manager, ProjectileManager* pMgr);

	void update(float dt) override;

	void spawnMinions() override;

	void retreat() override;



	void fireMissile(); 



	void useFlameThrower();

	void throwFireBomb();


};