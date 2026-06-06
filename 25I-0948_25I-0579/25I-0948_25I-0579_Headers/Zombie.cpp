#include "Zombie.h"
#include "GameConstants.h"
#include"PatrolState.h"
#include"Collider.h"
#include<iostream>
#include"Pistol.h"
#include"UndeadState.h"
#include"EntityManager.h"

Zombie::Zombie(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 20.0f, 20.0f, ColliderType::Enemy, 5, "Zombie", player) {

	// edit specific attributes
	fireRate = 1.0f;
	baseSpeed = 100.0f;
	currentState = new PatrolState();
	currentState->enter(this);

	baseScore = 100;

	weapon = new Pistol(500);
	typeId = EnemyType::ZOMBIE;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Enemy Zombie.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	int frames[] = { 4, 9, 10, 8 };
	float timers[] = { 0.2f, 0.2f, 0.15f, 0.15f };
	animator = new Animator(&sprite, 4, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::DIE] = 3;

}


void Zombie::update(float passedTime)
{

	// first i will call the update funtion of enemy for basic logic
	GroundEnemy::update(passedTime);

	// now i will check for the collission of player with zombie for undead state
	if (player != nullptr) {

		// here i will call my function from collider
		if (this->hitbox.checkCollision(player->getHitbox())) {

			// change the current state of player to undead
			player->changeState(new UndeadState);
		}
	}
}

void Zombie::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	int batchSize = 3 + rand() % 3;
	for (int i = 0; i < batchSize; i++) {
		Zombie* enemy = new Zombie(x + (i * 40.0f), y, player);
		enemy->setProjectileManager(pm);
		mgr->add(enemy);
	}
}

