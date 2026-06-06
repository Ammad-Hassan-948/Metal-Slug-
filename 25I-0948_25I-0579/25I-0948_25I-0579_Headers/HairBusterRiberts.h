#pragma once

#include "Boss.h"

class HairbusterRiberts :public Boss {

private:
	float rocketTimer;
	float bombTimer;
	float spawnTimer;

	//sinetimer to get a smooth hovering effect
	float sineTimer;

	float targetHeight;


public:

	HairbusterRiberts(float x, float y, PlayerSoldier* player, EntityManager*
		manager, ProjectileManager* pMgr);


	void update(float dt) override;

	void spawnMinions() override;

	void retreat() override;

	void fireRocket();


	void dropFireBomb();


};