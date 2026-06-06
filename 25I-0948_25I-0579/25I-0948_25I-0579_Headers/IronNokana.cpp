#include "IronNokana.h"
#include "RebelSoldier.h"
#include "EntityManager.h"
#include "ProjectileManager.h"

#include <iostream>


IronNokana::IronNokana(float x, float y, PlayerSoldier* player,
	EntityManager* manager, ProjectileManager* projectileManager): 
	Boss(x, y, 30, "Iron Nokana", player,
		manager, projectileManager) {

	missileTimer = 0;
	flamethrowerTimer = 0;
	minionsSpawnTimer = 2.0f;
	minionsKilled = 0;
	fireBombTimer = 0;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Iron nokana.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);

	int frames[] = { 3, 1, 1, 1 };
	float timers[] = { 0.2f, 0.15f, 0.15f, 0.2f };

	animator = new Animator(&sprite, 4, frames, timers, 256);


	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::SHOOT] = 1; // Turning
	animationRow[AnimationState::DIE] = 2;


	//this->width = 300.0f; this->height = 200.0f;
	//this->hitbox.setWidth(300.0f);
	//this->hitbox.setHeight(200.0f);

}


void IronNokana::update(float dt) {

	if (retreatTriggered) {

		positionX += 300.0f * dt; 

		if (positionX > player->getPositionX() + 800.0f) {
			hasRetreated = true;
			//isAlive = false;
			visible = false;
		}

		if (animator) animator->update(dt);
		hitbox.updateCoordinates(positionX, positionY);
		return;
	}


	missileTimer += dt;
	flamethrowerTimer += dt;
	fireBombTimer += dt;
	minionsSpawnTimer += dt;

	if (missileTimer > 2.5f) {
		fireMissile();

		missileTimer = 0;
	}

	if (flamethrowerTimer > 3.0f) {
		float distance = abs(player->getPositionX() - positionX);

		if (distance < 500.0f) {
			useFlameThrower();

			flamethrowerTimer = 0;
		}
		
	}

	if (fireBombTimer > 4.5f) {

		throwFireBomb();
		fireBombTimer = 0;

	}

	if (minionsSpawnTimer > 4.0f) {

		spawnMinions();

		minionsSpawnTimer = 0;
	}

	float targetX = player->getPositionX() - 500;
	//to stay at a certain distance from the player


	if (positionX < targetX) {

		velocityX = 50.0f;

	}


	else {
		velocityX = -40.0f;
	}

	positionX += velocityX * dt;
	positionY += velocityY * dt;

	if (velocityX > 0) direction = 1;
	else if (velocityX < 0) direction = -1;


	//else if (distance > 600.0f) {

	//	velocityX = 50.0f;
	//}


	//else {
	//	velocityX = 0;
	//}
	Boss::update(dt);
}



void IronNokana::spawnMinions() {

	std::cout << "Spawing minions " << std::endl;

	minionsSpawnedInBatch = 3;
	minionsKilledInBatch = 0;

	for (int i = 0; i < 3; i++) {

		Enemy* minion = new RebelSoldier(positionX - 50, positionY, player);
		minion->setParentBoss(this);
		minion->setProjectileManager(projectileManager);
		EntityMgr->add(minion);
	}
}


void IronNokana::retreat() {

	std::cout << "Iron Nokana Low Hp. Retreating " << endl;

	//handled in update
}


void IronNokana::fireMissile() {

	//launch from the top of the tank

	float launchX = positionX + 15.0f;
	float launchY = positionY;

	//calculating angle towards the player

	float dx = player->getPositionX() - launchX;
	float dy = player->getPositionY() - launchY + 50.0f;

	float angle = atan2(-dy, dx) * 180 / 3.14159f;

	projectileManager->spawnRocket(launchX, launchY, angle, 0);
	// t is 0 for enemy projectile
}



void IronNokana::useFlameThrower() {

	//hidden bottom locaiton on front bottom of the tank

	float fireX = positionX + ((direction == 1) ? 280.0f : 20.0f);

	float fireY = positionY + 160.0f;

	projectileManager->spawnFlame(fireX, fireY, (direction == 1) ? 0.0f : 180.0f, 0);
	projectileManager->spawnFlame(fireX, fireY, (direction == 1) ? 10.0f : 170.0f, 0);
	projectileManager->spawnFlame(fireX, fireY, (direction == 1) ? -10.0f : 190.0f, 0);



}


void IronNokana::throwFireBomb() {

	float launchX = positionX + 100.0f;

	float launchY = positionY + 50.0f;

	float vx = (direction == 1) ? 400.0f : -400.0f;

	float vy = -600.0f;

	projectileManager->spawnFireBombGrenade(launchX, launchY, vx, vy, 0);
}
