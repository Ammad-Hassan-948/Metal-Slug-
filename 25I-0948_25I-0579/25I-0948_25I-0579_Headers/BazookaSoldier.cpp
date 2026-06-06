#include "BazookaSoldier.h"
#include "GameConstants.h"
#include"PatrolState.h"
#include<iostream>
#include"RocketLauncher.h"
#include<cmath>
#include"EntityManager.h"
#include"ParatrooperState.h"

using namespace std;

BazookaSoldier::BazookaSoldier(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 0.0f, 40.0f, ColliderType::Enemy, 2, "Bazooka Soldier", player) {


	// edit specific attributes
	this->hp = 2;
	fireRate = 0.5f;
	baseSpeed = 150.0f;
	currentState = new PatrolState();
	currentState->enter(this);
	baseScore = 100;
	

	weapon = new RocketLauncher(100);
	typeId = EnemyType::BAZOOKA_SOLDIER;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Bazooka Soldier.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);


	int frames[] = { 3, 4, 5, 4, 3, 2 };
	
	float timers[] = { 0.2f, 0.12f, 0.2f, 0.2f, 0.2f, 0.2f };

	
	animator = new Animator(&sprite, 6, frames, timers, 64);

	// Animation rows
	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::DIE] = 3;
	animationRow[AnimationState::CELEBRATE] = 4;
	animationRow[AnimationState::PARATROOPER] = 5;

}

void BazookaSoldier::fireWeapon()
{
	if (weapon != nullptr && player != nullptr) {

		// first i will get the centres for the enemy and the players both for distance between their centres
		float enemyX = positionX + hitbox.getWidth() / 2;
		float enemyY = positionY + hitbox.getHeight() / 2;

		// now for player
		float playerX = player->getPositionX() + player->getHitbox().getWidth() / 2;
		float playerY = player->getPositionY() + player->getHitbox().getHeight() / 2;

		// now find the distances between their centres both x and y
		float distX = playerX - enemyX;
		float distY = playerY - enemyY;

		// now i will find the angle use atan2 which will give us exactly the angle also considering the quadrant, if we use only atan it does not consider the 
		// quadrant and only gives the angle
		// using -dy as math coordinates and screen coordinates are different in screen 0,0 is upwards and if player is upward to enemy than 
	    // difference would be negative so to shoot up we must negate dy
		float angle = atan2(-distY, distX);
		// now as this in radians to convert it into degrees
		angle *= (180.0f / 3.14159265f);

		Projectile* rocket = weapon->fire(enemyX, enemyY, direction, angle, this);

		
	}

	

}

void BazookaSoldier::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper)
{
	int batchSize = 1 + rand() % 2;
	for (int i = 0; i < batchSize; i++) {
		BazookaSoldier* enemy = new BazookaSoldier(x + (i * 40.0f), y, player);
		enemy->setProjectileManager(pm);

		if (paratrooper) {

			enemy->baseScore += 25;

			enemy->setIsParatrooper(true);
			enemy->changeAIState(new ParatrooperState());
		}
		mgr->add(enemy);
	}
}
