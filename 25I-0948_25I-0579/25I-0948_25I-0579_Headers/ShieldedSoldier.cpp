#include "ShieldedSoldier.h"
#include "GameConstants.h"
#include"Pistol.h"
#include"Weapon.h"
#include"EnemyAIState.h"
#include"PatrolState.h"
#include"EntityManager.h"
#include"ParatrooperState.h"

ShieldedSoldier::ShieldedSoldier(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 20.0f, 20.0f, ColliderType::Enemy, 5, "Shielded Soldier", player) {

	// edit specific attributes
	fireRate = 0.5f;
	baseSpeed = 150.0f;
	currentState = new PatrolState();
	currentState->enter(this);

	baseScore = 75;

	weapon = new Pistol(500);
	typeId = EnemyType::SHIELDED_SOLDIER;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Shielded Soldier.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	int frames[] = { 3, 4, 4, 4, 3, 2 };

	float timers[] = { 0.2f, 0.12f, 0.2f, 0.2f, 0.2f, 0.2f };

	animator = new Animator(&sprite, 6, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::DIE] = 3;
	animationRow[AnimationState::CELEBRATE] = 4;
	animationRow[AnimationState::PARATROOPER] = 5;

}


void ShieldedSoldier::takeDamage(int amount, bool meleeAttack)
{
	// first i would track a boolean to check if we take hit or not
	bool takeHit = false;
	
	// as all our explosives give hp damage > 5
	if (amount >= 5) {
		// we will take damage if explosive hits
		takeHit = true;
	}
	// if no then we would check the direction
	else if (player != nullptr) {

		// first i will check if enemy got hit from right up
		float playerPos = player->getPositionY() + player->getHitbox().getHeight();
		// i am adding 30 in enemy position as a safety measure
		if (playerPos < positionY + 30.0f) {
			takeHit = true;
		}
		// else i will check both left and right direction
		else {

			if (this->direction == 1 && player->getPositionX() < this->positionX)
				takeHit = true;
			else if (this->direction == -1 && player->getPositionX() > this->positionX)
				takeHit = true;
		}
	}

	// now i will check if soldier has taken hit
	if (takeHit) {
		hp -= amount;
		if (hp < 0)
			die();
	}

	// else the attack will be blocked and nothing happens
}

void ShieldedSoldier::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm, bool paratrooper)
{
	int batchSize = 2 + rand() % 3;
	for (int i = 0; i < batchSize; i++) {
		ShieldedSoldier* enemy = new ShieldedSoldier(x + (i * 70.0f), y, player);

		if (paratrooper) {

			// if it is paratrooper add another 25
			enemy->baseScore += 25;

			enemy->setIsParatrooper(true);
			enemy->changeAIState(new ParatrooperState());
		}
		enemy->setProjectileManager(pm);
		mgr->add(enemy);
	}
}

