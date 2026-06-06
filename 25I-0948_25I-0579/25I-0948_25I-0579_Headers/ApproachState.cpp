#include "ApproachState.h"
#include"Enemy.h"
#include"AttackState.h"

ApproachState::ApproachState()
{
}

void ApproachState::enter(Enemy* enemy)
{
	enemy->doAnimation(AnimationState::MOVE);
}

void ApproachState::update(Enemy* enemy, float passedTime)
{
	// here i will check for the player where is it
	PlayerSoldier* player = enemy->getPlayer();

	if (player->getPositionX() < enemy->getPositionX()) {
		
		enemy->setDirection(-1);
		float newX = enemy->getPositionX() - enemy->getBaseSpeed() * passedTime;
		enemy->setPositionX(newX);
	}
	else if (player->getPositionX() > enemy->getPositionX()) {

		enemy->setDirection(1);
		float newX = enemy->getPositionX() + enemy->getBaseSpeed() * enemy->getDirection() * passedTime;
		enemy->setPositionX(newX);
	}

	// now i will also check for distance to trigger the attack state, i have set 800 as the attack range
	if (abs(player->getPositionX() - enemy->getPositionX()) < 600) {
		enemy->changeAIState(new AttackState);
	}
}
