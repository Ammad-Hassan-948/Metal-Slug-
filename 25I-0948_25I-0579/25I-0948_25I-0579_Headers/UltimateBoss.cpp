#include "UltimateBoss.h"
#include "SupplyCrate.h"
#include "EntityManager.h"
#include "ProjectileManager.h"
#include "RebelSoldier.h"
#include "FlyingTara.h"
#include "EnemySub.h"
#include <cmath>
#include <iostream>
#include"ScoreManager.h"



UltimateBoss::UltimateBoss(float x, float y, PlayerSoldier* player,
	EntityManager* mgr, ProjectileManager* pMgr) : Boss(x, y, 90, "The Ultimate Boss", player, mgr, pMgr) {



	groundPart = new IronNokana(x, y, player, mgr, pMgr);
	aerialPart = new HairbusterRiberts(x, y, player, mgr, pMgr);
	aquaticPart = new SeaSatan(x, y, player, mgr, pMgr);

	currentMode = BossMode::GROUND;
	modeTimer = 0;
	attackTimer = 0;
	sineTimer = 0;
	aloneBoss = false;

}

void UltimateBoss::takeDamage(int amount, bool meleeAttack) {
	// Forward damage to the current active boss part
	if (currentMode == BossMode::GROUND) groundPart->takeDamage(amount);
	else if (currentMode == BossMode::AERIAL) aerialPart->takeDamage(amount);
	else if (currentMode == BossMode::AQUATIC) aquaticPart->takeDamage(amount);

	// Sync total HP
	this->hp = groundPart->getHp() + aerialPart->getHp() + aquaticPart->getHp();

	// if the total hp is still greater than 0 then check for every part
	if (this->hp > 0) {

		// check if current part is dead
		bool currDead = (currentMode == BossMode::GROUND && groundPart->getHp() <= 0) ||  
			            (currentMode == BossMode::AERIAL && aerialPart->getHp() <= 0) ||
		                (currentMode == BossMode::AQUATIC && aquaticPart->getHp() <= 0);


		if (currDead) {

			// we will switch the state
			switchMode();
			modeTimer = 0.0f;
		}


	}

	
}

void UltimateBoss::render(sf::RenderWindow& window, Camera& cam) {

	if (currentMode == BossMode::GROUND) {
		groundPart->render(window, cam);
	}
	else if (currentMode == BossMode::AERIAL) {
		aerialPart->render(window, cam);
	}
	else if (currentMode == BossMode::AQUATIC) {
		aquaticPart->render(window, cam);
	}
}

void UltimateBoss::update(float dt) {
	modeTimer += dt;


	char currentTile = projectileManager->getTileDesignAt(positionX + hitbox.getWidth() / 2, positionY + hitbox.getHeight());

	// if the tile at this place is of water and current mode is not aquatic i will switch to aquatic
	if (currentTile == '~' && currentMode != BossMode::AQUATIC) {
		currentMode = BossMode::AQUATIC;
		modeTimer = 0; // Reset timer because we switched biomes

	}
	// if not aquatic and is Space i will switch to space
	else if (currentTile != '~' && currentTile != ' ' && currentMode == BossMode::AQUATIC) {
		currentMode = BossMode::GROUND;
		modeTimer = 0;

	}





	if (modeTimer > 15.0f) {
		switchMode();
		modeTimer = 0;
	}

	
	if (currentMode == BossMode::GROUND && groundPart->getHp() > 0) {

		groundPart->setPositionX(this->positionX);

		groundPart->setPositionY(this->positionY);

		groundPart->update(dt);

		this->positionX = groundPart->getPositionX();
		this->positionY = groundPart->getPositionY();

	}
	else if (currentMode == BossMode::AERIAL && aerialPart->getHp() > 0) {

		aerialPart->setPositionX(this->positionX);

		aerialPart->setPositionY(this->positionY);

		aerialPart->update(dt);

		this->positionX = aerialPart->getPositionX();
		this->positionY = aerialPart->getPositionY();

	}



	else if (currentMode == BossMode::AQUATIC && aquaticPart->getHp() > 0) {
		aquaticPart->setPositionX(this->positionX);

		aquaticPart->setPositionY(this->positionY);

		aquaticPart->update(dt);

		this->positionX = aquaticPart->getPositionX();
		this->positionY = aquaticPart->getPositionY();
	}


	this->hp = groundPart->getHp() + aerialPart->getHp() + aquaticPart->getHp();

	if (this->hp <= 0) {
		retreat();
	}
}

void UltimateBoss::spawnMinions() {
	
	int count = 2 + (rand() % 3);


	for (int i = 0; i < count; i++) {


		if (currentMode == BossMode::GROUND) groundPart->spawnMinions();


		else if (currentMode == BossMode::AERIAL) aerialPart->spawnMinions();

		else if (currentMode == BossMode::AQUATIC) aquaticPart->spawnMinions();

	}
}

void UltimateBoss::retreat() {
	std::cout << "ultimate boss is destroyed " << std::endl;

	ScoreManager::addScore(1500);

	hasRetreated = true; 
}

void UltimateBoss::switchMode() {
	int nextMode = (currentMode + 1) % 3;

	
	for (int i = 0; i < 3; i++) {

		if (nextMode == BossMode::GROUND && groundPart->getHp() > 0) break;

		if (nextMode == BossMode::AERIAL && aerialPart->getHp() > 0) break;

		if (nextMode == BossMode::AQUATIC && aquaticPart->getHp() > 0) break;

		nextMode = (nextMode + 1) % 3;
	}


	currentMode = nextMode;
}


