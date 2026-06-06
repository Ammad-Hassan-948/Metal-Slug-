#pragma once
#include "Boss.h"

class SeaSatan :public Boss {

private:
	float hmgTimer;
	float rocketTimer;
	float spawnTimer;


public:

	SeaSatan(float x, float y, PlayerSoldier* player,
		EntityManager* mgr, ProjectileManager* pMgr);

	void update(float dt) override;

	void spawnMinions() override;

	void retreat() override;


	void fireHMG();

	void fireTorpedo();


};
