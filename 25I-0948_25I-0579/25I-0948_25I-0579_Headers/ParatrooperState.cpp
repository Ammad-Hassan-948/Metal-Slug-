#include "ParatrooperState.h"
#include"Enemy.h"
#include"PatrolState.h"

ParatrooperState::ParatrooperState() {}

void ParatrooperState::enter(Enemy* enemy)
{
	// here i will change the sprite sheet to paratrooper
	enemy->setIsParatrooper(true);
	enemy->doAnimation(AnimationState::PARATROOPER);
}

void ParatrooperState::update(Enemy* enemy, float passedTime)
{
	if (enemy->getOnGround()) {

		// this means the paratrooper has reached ground so switch to normal state
		exit(enemy);
		enemy->changeAIState(new PatrolState);
		return;
	}

	// if not we continue to move it down slowly
	float downSpeed = 50.0f;
	float newPosY = enemy->getPositionY() + (downSpeed * passedTime);

	enemy->setPositionY(newPosY);
}

void ParatrooperState::exit(Enemy* enemy)
{
	// here change the sprite back to normal
	enemy->setIsParatrooper(false);
	enemy->doAnimation(AnimationState::IDLE);
}

