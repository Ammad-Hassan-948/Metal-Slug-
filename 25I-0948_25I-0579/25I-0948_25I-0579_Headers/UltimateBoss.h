#pragma once
#include"Boss.h"
#include"IronNokana.h"
#include "HairBusterRiberts.h"
#include"SeaSatan.h"

//class PlayerSoldier;

struct BossMode {
	static const int GROUND = 0;
	static const int AERIAL = 1;
	static const int AQUATIC = 2;
};



class UltimateBoss :public Boss {


private:
	IronNokana* groundPart; HairbusterRiberts* aerialPart;
	SeaSatan* aquaticPart;

	int currentMode;
	float modeTimer;
	float attackTimer;
	float sineTimer;

public:
	UltimateBoss(float x, float y, PlayerSoldier* player, EntityManager* manager, ProjectileManager* pMgr);


	void update( float dt) override;
	void takeDamage(int amount, bool meleeAttack = false) override;
	void spawnMinions() override;

	void retreat() override;


	void switchMode();


	void render(sf::RenderWindow& window, Camera& cam) override;
};