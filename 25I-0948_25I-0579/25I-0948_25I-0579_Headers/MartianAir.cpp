#include "MartianAir.h"
#include "GameConstants.h"
#include"TransformationState.h"
#include"PatrolState.h"
#include"LaserGun.h"
#include"MartianGround.h"
#include"EntityManager.h"
#include"ParatrooperState.h"
#include"HoverState.h"

MartianAir::MartianAir(float startX, float startY, PlayerSoldier* player) :
	AirEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 20.0f, 20.0f, ColliderType::Enemy, 2, "Martian", player) {

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Martian.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	// edit specific attributes
	this->hp = 2;
	fireRate = 4.0f;
	baseSpeed = 150.0f;
	currentState = new HoverState();
	currentState->enter(this);

	baseScore = 200;


	weapon = new LaserGun(500);
	typeId = EnemyType::MARTIAN;

	int frames[] = { 4, 2, 4, 4, 5, 6 };
	float timers[] = { 0.15f, 0.1f, 0.2f, 0.15f, 0.15f, 0.15f };
	animator = new Animator(&sprite, 6, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 0;      // In pod
	animationRow[AnimationState::PARATROOPER] = 1; // Falling

	
}

void MartianAir::update(float passedTime)
{
	AirEnemy::update(passedTime);

}

void MartianAir::die()
{
	MartianGround* ground = new MartianGround(this->positionX, this->positionY, player);
	ground->setIsParatrooper(true);
	ground->changeAIState(new ParatrooperState());
	
	if (this->manager != nullptr) {
		this->manager->add(ground); // Add to the manager so it actually appears!

	}
	
	this->isAlive = false;
}

void MartianAir::fireWeapon()
{
	if (weapon != nullptr && player != nullptr) {

		float enemyX = positionX + hitbox.getWidth() / 2;
		float enemyY = positionY + hitbox.getHeight() / 2;

		// calculate the accurate angle to hit the player
		float dx = player->getPositionX() - enemyX;
		float dy = player->getPositionY() - enemyY;
		float angle = atan2(-dy, dx) * 180.0f / 3.14159f;

		weapon->fire(enemyX, enemyY, direction, angle, this);

	}
}

void MartianAir::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	
	MartianAir* enemy = new MartianAir(x + 64.0f, y, player);
	enemy->setProjectileManager(pm);
	mgr->add(enemy);
	
}

