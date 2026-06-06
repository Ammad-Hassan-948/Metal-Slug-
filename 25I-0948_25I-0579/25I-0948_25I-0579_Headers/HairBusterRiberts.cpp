#include "HairBusterRiberts.h"

#include "FlyingTara.h"
#include "MartianAir.h"

#include "EntityManager.h"

#include "ProjectileManager.h"

#include <cmath>



HairbusterRiberts::HairbusterRiberts(float x, float y, PlayerSoldier* player, EntityManager* manager, ProjectileManager* pManager):Boss(x, y, 30, "HairBuster Riberts", player, manager, pManager) 

{

	rocketTimer = 0;
	bombTimer = 0;
	spawnTimer = 3;
	sineTimer = 0;
	targetHeight = y;


	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/HairBuster Riberts.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);

	int frames[] = { 1, 1 };
	float timers[] = { 0.2f, 0.2f };

	animator = new Animator(&sprite, 2, frames, timers, 256);


	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::DIE] = 1;

	//this->width = 250.0f;
	//this->height = 150.0f;

}


void HairbusterRiberts::update(float dt) {

	if (retreatTriggered) {

		positionX -= 200.0f * dt;
		positionY += 100.0f * dt;

		if (positionX < player->getPositionX() - 1000.0f) {

			hasRetreated = true;
			visible = false;
		}

		Boss::update(dt);
		return;
	}

	rocketTimer += dt; bombTimer += dt;
	spawnTimer += dt; sineTimer += dt;

	//bobbing up and down slightly 
	float bobbing = std::sin(sineTimer * 2.0f) * 40.0f;
	float currentTargetY = targetHeight + bobbing;

	//smooth move to the target
	if (positionY < currentTargetY) {

		velocityY = 50.0f;
	}

	else {

		velocityY = -50.0f;
	}

	//horizontal following

	float distanceToPlayer = player->getPositionX() - positionX;

	if (std::abs(distanceToPlayer) > 400.0f) {

		velocityX = (distanceToPlayer > 0) ? 100.0f : -100.0f;
	}

	else {
		velocityX = 0;
	}

	positionX += velocityX * dt;
	positionY += velocityY * dt;

	if (velocityX > 0) direction = 1;
	else if (velocityX < 0) direction = -1;


	if (rocketTimer > 1.8f) {

		fireRocket(); rocketTimer = 0;
	}

	if (bombTimer > 3.0f && std::abs(distanceToPlayer) < 200.0) {

		dropFireBomb(); bombTimer = 0;
	}

	if (spawnTimer > 5.0f) {

		spawnMinions();

		spawnTimer = 0;
	}


	Boss::update(dt);
}

void HairbusterRiberts::spawnMinions()
{
	minionsSpawnedInBatch = 2;
	minionsKilledInBatch = 0;

	Enemy* m1 = new FlyingTara(positionX - 100, positionY, player);
	m1->setParentBoss(this);
	m1->setProjectileManager(projectileManager);
	EntityMgr->add(m1);

	Enemy* m2 = new MartianAir(positionX + 300, positionY, player);
	m2->setParentBoss(this);
	m2->setProjectileManager(projectileManager);
	EntityMgr->add(m2);
}

void HairbusterRiberts::retreat() {
	//handled in update
}

void HairbusterRiberts::fireRocket()
{
	float muzzleX = positionX + ((direction == 1) ? 200.0 : 50.0f);
	float muzzleY = positionY + 100.0f;


	float dx = player->getPositionX() - muzzleX; float dy = player->getPositionY() - muzzleY;

	float angle = std::atan2(dy, dx) * 180.0 / 3.14159f;

	projectileManager->spawnRocket(muzzleX, muzzleY, angle, 0);

}

void HairbusterRiberts::dropFireBomb() {

	float dropX = positionX + 125.0f;

	float dropY = positionY + 120.0f;

	projectileManager->spawnFireBombGrenade(dropX, dropY, 0.0f, 200.0f, 0);
}

