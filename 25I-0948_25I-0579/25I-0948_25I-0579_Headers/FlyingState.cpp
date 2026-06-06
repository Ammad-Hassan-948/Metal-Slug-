#include "FlyingState.h"
#include"Enemy.h"
#include"AttackState.h"
#include"ApproachState.h"

FlyingState::FlyingState()
{
	hoverTimer = 0.0f;
}

void FlyingState::enter(Enemy* enemy)
{
	enemy->doAnimation(AnimationState::MOVE);
}

void FlyingState::update(Enemy* enemy, float passedTime)
{
	// for hover state i am going to use an effet of moving the pod up and down to show hover by using a sin wave
	// i find this hovering distance by changing the sin wave according to time passed which increases
	hoverTimer += passedTime;
	float hovering = sin(hoverTimer * 2.0f) * 0.5f;
	enemy->setPositionY(enemy->getPositionY() + hovering);

	// also now for the x position i will make sure my martian for which specifically this state is comes right under the enemy by following him
	// first i get the player to follow it
	PlayerSoldier* player = enemy->getPlayer();

	// now i will change direction of martian based on position of player
	if (player->getPositionX() < enemy->getPositionX()) {
		
		enemy->setDirection(-1);
		float newPosX = enemy->getPositionX() - enemy->getBaseSpeed() * passedTime;
		enemy->setPositionX(newPosX);
	}
	else if (player->getPositionX() > enemy->getPositionX()) {
		enemy->setDirection(1);
		float newPosX = enemy->getPositionX() + enemy->getBaseSpeed() * passedTime;
		enemy->setPositionX(newPosX);
	}

	// if my enemy gets right above the player with a good distance, also for the x distance as this is an explosive so i have also made sure that
	// the player must be in x range of enemy by 30 pixels too and not far from that
	if (player->getPositionY() >= enemy->getPositionY() && abs(player->getPositionX() - enemy->getPositionX()) < 30) {
		// here i will fire the energy beam by first changing to attack state
		enemy->changeAIState(new ApproachState);

	}
}

