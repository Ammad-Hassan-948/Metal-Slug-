#include"SeaSatan.h"
#include"EnemySub.h"
#include "EntityManager.h"

#include "ProjectileManager.h"

SeaSatan::SeaSatan(float x, float y, PlayerSoldier* player, EntityManager* mgr,
	ProjectileManager* pMgr) :
	Boss(x, y, 30, "Sea Satan", player, mgr, pMgr) {

	hmgTimer = 0;
	rocketTimer = 0;
	spawnTimer = 0;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Sea Satan.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);

	int frames[] = {1, 1 };
	float timers[] = { 0.2f, 0.2f };

	animator = new Animator(&sprite, 2, frames, timers, 512);


	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::DIE] = 1;

	//this->width = 400.0f;
	//this->height = 150.0f;

}

void SeaSatan::update(float dt) {


	if (retreatTriggered) {

		positionX += 150.0f * dt;

		//if (positionX > player->getPositionX() + 1500.0f) {
			hasRetreated = true;
			visible = false;
		


		Boss::update(dt); return;
	}


	hmgTimer += dt;
	rocketTimer += dt;
	spawnTimer += dt;


	if (hmgTimer > 0.8f) {
		fireHMG();
		hmgTimer = 0;
	}

	if (rocketTimer > 4.0f) {
		fireTorpedo();
		rocketTimer = 0;
	}

	if (spawnTimer > 10.0f) {
		spawnMinions();
		spawnTimer = 0;
	}

	static float moveTime = 0;
	moveTime += dt;

	velocityX = 60.0f * std::sin(moveTime * 0.5f);

	positionX += velocityX * dt;
	positionY += velocityY * dt;

	if (velocityX > 0) direction = 1;
	else if (velocityX < 0) direction = -1;

	Boss::update(dt);
}


void SeaSatan::fireHMG() {

	float dx = player->getPositionX() - (positionX + 200);
	float dy = player->getPositionY() - (positionY + 80);
	float angle = atan2(dy, dx) * 180.0f / 3.14159f;

	projectileManager->spawnBullet(positionX + 50, positionY + 80, angle, 3, 600, ColliderType::EnemyBullet);
	projectileManager->spawnBullet(positionX + 350, positionY + 80, angle, 3, 600, ColliderType::EnemyBullet);


}


void SeaSatan::fireTorpedo() {

	float dx = player->getPositionX() - (positionX + 200);
	float dy = player->getPositionY() - (positionY + 50);
	float angle = atan2(dy, dx) * 180.0f / 3.14159f;

	projectileManager->spawnRocket(positionX + 200, positionY + 50, angle, ColliderType::EnemyBullet);
}


void SeaSatan::spawnMinions(){
	minionsSpawnedInBatch = 1;
	minionsKilledInBatch = 0;

	Enemy* minion = new EnemySub(positionX - 200, positionY + 100, player);
	minion->setParentBoss(this);
	minion->setProjectileManager(projectileManager);
	EntityMgr->add(minion);
}

void SeaSatan::retreat() {

	//retreat logic is hadndled in update
}


