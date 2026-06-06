#include "RebelSoldier.h"
#include "GameConstants.h"
#include"PatrolState.h"
#include"Collider.h"
#include<iostream>
#include"Pistol.h"
#include"EntityManager.h"
#include"ParatrooperState.h"

RebelSoldier::RebelSoldier(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 20.0f, 20.0f, ColliderType::Enemy, 2, "Rebel Soldier", player) { 
	
	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Soldier.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	// edit specific attributes
	this->hp = 2;
	fireRate = 1.0f + (float)(rand() % 100) / 100.0f; 
	baseSpeed = 130.0f + (float)(rand() % 40); 
	currentState = new PatrolState();
	currentState->enter(this);
	baseScore = 50;

	weapon = new Pistol(500);
	typeId = EnemyType::REBEL_SOLDIER;

	int frames[] = { 3, 7, 3, 4, 3, 2 };

	float timers[] = { 0.2f, 0.15f, 0.1f, 0.15f, 0.2f, 0.2f };


	animator = new Animator(&sprite, 6, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::DIE] = 3;
	animationRow[AnimationState::CELEBRATE] = 4;
	animationRow[AnimationState::PARATROOPER] = 5;

}

void RebelSoldier::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper)
{
	int batchSize = 2 + rand() % 3;
	for (int i = 0; i < batchSize; i++) {
		RebelSoldier* enemy = new RebelSoldier(x + (i * 70.0f), y, player);

		if (paratrooper) {

			enemy->baseScore += 25;

			enemy->setIsParatrooper(true);
			enemy->changeAIState(new ParatrooperState());
		}
		enemy->setProjectileManager(pm);
		mgr->add(enemy);
	}
}


