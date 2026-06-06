#include "Enemy.h"
#include"EnemyAIState.h"
#include"Weapon.h"
#include "ProjectileManager.h"
#include"Boss.h"
#include"ScoreManager.h"

Enemy::Enemy(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name, PlayerSoldier* player) :
	DamagableEntity(startX, startY, velocityX, velocityY, gravity, width, height, offsetX, offsetY, colliderType, hp, name), player(player), typeId(-1) {
	currentState = nullptr;
	oldState = nullptr;
	weapon = nullptr;
	killedByMelee = false;
	baseScore = 0;

}

Enemy::~Enemy()
{
	delete currentState;
	delete weapon;
}

PlayerSoldier* Enemy::getPlayer() const
{
	return player;
}

void Enemy::changeAIState(EnemyAIState* newState)
{
	if (currentState != nullptr) {
		// change conditions back and save this state is old
		currentState->exit(this);
		oldState = currentState;
	}
	currentState = newState;
	// also update condition
	this->currentState->enter(this);
}

void Enemy::update(float passedTime)
{
	// here now i will check if it is dying and is in last frame then set isAlive = false
	if (isDying) {

		if (animator != nullptr) {

			// update only the animator and skip rest logic if it is dying
			animator->update(passedTime);

			if (animator->isLastFrame())
				isAlive = false;
		}

		return;
	}

	// first delete the old state if there is any
	if (oldState != nullptr) {
		delete oldState;
		oldState = nullptr;
	}

	if (currentState != nullptr)
		// call update on the current state
		currentState->update(this, passedTime);

	// also keep updating the hitbox 
	this->hitbox.updateCoordinates(positionX, positionY);


	if (animator != nullptr) {
		// if direction is -1 flip the direction of sprite so it can show to left
		if (direction == -1)
			animator->setFlipDir(true);
		// else flip to show it to right
		else
			animator->setFlipDir(false);

		animator->update(passedTime);
	}
}

bool Enemy::playerInRange(float threshholdX)
{
	// first find distance x
	float distanceX = abs(player->getPositionX() - positionX);

	if (distanceX < threshholdX) {

		// if distance is very less return true
		if (distanceX < 50.0f) return true;

		// now check the direction where they are
		// if enemy facing right and player is also to right so attack
		if (this->direction == 1 && player->getPositionX() > positionX)
			return true;
		// if enemy facing left and player to the left
		if (this->direction == -1 && player->getPositionX() < positionX)
			return true;
	}

	return false;
}

void Enemy::fireWeapon()
{
	if (weapon != nullptr) {

		float enemyX = positionX + hitbox.getWidth() / 2;
		float enemyY = positionY + hitbox.getHeight() / 2;

		float angle = (direction == 1) ? 0.0f : 180.0f;

		// Use the internal weapon to fire, which now uses projMgr
		weapon->fire(enemyX, enemyY, direction, angle, this);
	}
}

void Enemy::takeDamage(int amount, bool meleeAttack)
{
	hp -= amount;

	if (meleeAttack)
		killedByMelee = true;
	      
	if (hp <= 0) {
		doAnimation(AnimationState::DIE);
		die();
	}
}

void Enemy::die()
{
	// if player is not already in dying animation i will first do it
	if (!isDying) {
		isDying = true;

		// adding base kill score
		ScoreManager::addScore(this->baseScore);

		// for aerial Kill
		if (!onGround) {
			ScoreManager::addScore(100);
		}

		// for melee kill
		if (killedByMelee) {
			ScoreManager::addScore(50);
		}

		doAnimation(AnimationState::DIE);

		if (parentBoss != nullptr) {
			// Notify boss that a minion has died to track batches
			parentBoss->notifyMinionDeath();
		}
	}

}

void Enemy::setPlayer(PlayerSoldier* p)
{
	player = p;
}

bool Enemy::getIsParatrooper() const
{
	// this is a base implementation specific child classes will override it
	return false;
}

void Enemy::setProjectileManager(ProjectileManager* pm)
{
	if (weapon != nullptr)
		weapon->setProjectileManager(pm);
}
