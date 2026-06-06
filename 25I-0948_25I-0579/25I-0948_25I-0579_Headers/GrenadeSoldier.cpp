#include "GrenadeSoldier.h"
#include "GameConstants.h"
#include"EntityManager.h"
#include"PatrolState.h"
#include<iostream>
#include"GrenadeWeapon.h"
#include<cmath>
#include"ParatrooperState.h"

using namespace std;

GrenadeSoldier::GrenadeSoldier(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 0.0f, 40.0f, ColliderType::Enemy, 2, "Grenade Soldier", player) {

	// edit specific attributes
	fireRate = 0.5f;
	baseSpeed = 150.0f;
	currentState = new PatrolState();
	currentState->enter(this);

	baseScore = 100;

	weapon = new GrenadeWeapon(-1);
	typeId = EnemyType::GRENADE_SOLDIER;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Grenade Soldiers.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	//float timers[] = { 0.2f, 0.12f, 0.2f, 0.2f, 0.2f };

	int frames[] = { 3, 3, 6, 4, 2};
	float timers[] = { 0.2f, 0.15f, 0.25f, 0.15f, 0.2f };
	animator = new Animator(&sprite, 5, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::THROW_GRENADE] = 2;
	animationRow[AnimationState::DIE] = 3;
	animationRow[AnimationState::PARATROOPER] = 4;

}

void GrenadeSoldier::fireWeapon()
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
		float angle = atan2(distY, distX);
		// now as this in radians to convert it into degrees
		angle *= (180.0f / 3.14159265f);

		Projectile* grenade = weapon->fire(enemyX, enemyY, direction, angle, this);

		
	}



}

void GrenadeSoldier::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper)
{
	int batchSize = 1 + rand() % 2;
	for (int i = 0; i < batchSize; i++) {
		GrenadeSoldier* enemy = new GrenadeSoldier(x + (i * 40.0f), y, player);
		
		if (paratrooper) {

			enemy->baseScore += 25;

			enemy->setIsParatrooper(true);
			enemy->changeAIState(new ParatrooperState());
		}
		enemy->setProjectileManager(pm);
		mgr->add(enemy);
	}
}


