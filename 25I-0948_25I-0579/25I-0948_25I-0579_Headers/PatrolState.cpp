#include "PatrolState.h"
#include"AttackState.h"
#include"Enemy.h"



PatrolState::PatrolState()
{
	// keep a randomized timer between 2 and 5 seconds
	patrolTimer = 2.0f + (float)(rand() % 300) / 100.0f;
}

void PatrolState::enter(Enemy* enemy)
{
	// here i will set the animation for walking
	enemy->doAnimation(AnimationState::MOVE);

}

void PatrolState::update(Enemy* enemy, float passedTime)
{

	// first i will get all the current attributes
	float currentX = enemy->getPositionX();
	
	float change = enemy->getBaseSpeed() * enemy->getDirection() * passedTime;

	enemy->setPositionX(currentX + change);

	patrolTimer -= passedTime;

	// now after moving look for the timer if timer has reached change direction and reset timer
	if (patrolTimer <= 0.0f) {
		enemy->setDirection(-enemy->getDirection());
		patrolTimer = 2.0f + (float)(rand() % 300) / 100.0f;
	}

	if (enemy->playerInRange(600.0f)) {
		enemy->changeAIState(new AttackState);
		return;
	}


}



