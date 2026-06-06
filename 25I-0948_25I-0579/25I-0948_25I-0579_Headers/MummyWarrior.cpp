#include "MummyWarrior.h"
#include "GameConstants.h"
#include"PatrolState.h"
#include"MummyState.h"
#include"EntityManager.h"

MummyWarrior::MummyWarrior(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 20.0f, 20.0f, ColliderType::Enemy, 5, "Mummy Warrior", player) {

	// edit specific attributes
	baseSpeed = 100.0f;
	currentState = new PatrolState();
	currentState->enter(this);

	hasCrumbled = false;
	resurrectionTimer = 3.0f;

	baseScore = 150;

	weapon = nullptr;
	typeId = EnemyType::MUMMY;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Enemy Mummy.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	int frames[] = { 4, 6, 4, 6, 5 };
	float timers[] = { 0.2f, 0.2f, 0.3f, 0.2f, 0.15f };
	animator = new Animator(&sprite, 5, frames, timers, 64);


	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::DIE] = 2;
	animationRow[AnimationState::SPECIAL_1] = 3; 

	// I will map the final death frame to  in the functions 

}

void MummyWarrior::fireWeapon()
{
	// empty as mummy do not fire weapon
}

void MummyWarrior::takeDamage(int amount, bool meleeAttack)
{
	if (hasCrumbled || !isAlive)
		return;

	// first i will check if damage is >5 then the mummy warrior would instantly die as it is in explosive
	if (amount >= 5) {

		hp -= amount;
		animationRow[AnimationState::DIE] = 4;
		doAnimation(AnimationState::DIE);

		die();     // as total hp is 5 so it would die
	}
	else {
		// means it is a bullet etc
		hp -= amount;

		if (hp <= 0) {
			// this means it will go to crumble
			hasCrumbled = true;
			resurrectionTimer = 3.0f;

			animator->setState(animationRow[AnimationState::DIE]);
		}
	}
}

void MummyWarrior::update(float passedTime)
{

	if (hasCrumbled) {
		resurrectionTimer -= passedTime;


		if (resurrectionTimer <= 0.0f) {
			// we will go back to normal by restoring hp
			hasCrumbled = false;
			hp = 5;
		}

		return;
	}

	// first i will call the update funtion of enemy for basic logic
	GroundEnemy::update(passedTime);

	// now i will check for the collission of player with zombie for undead state
	if (player != nullptr) {

		// here i will call my function from collider
		if (this->hitbox.checkCollision(player->getHitbox())) {

			// change the current state of player to undead
			player->changeState(new MummyState);
		}
	}
}

void MummyWarrior::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	
	MummyWarrior* enemy = new MummyWarrior(x + 40.0f, y, player);


	enemy->setProjectileManager(pm);
	mgr->add(enemy);
	
}

