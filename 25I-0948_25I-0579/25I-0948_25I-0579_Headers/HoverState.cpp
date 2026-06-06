#include "HoverState.h"
#include<cmath>
#include"Enemy.h"
#include"AttackState.h"

HoverState::HoverState()
{
	hoverTimer = 0.0f;
}

void HoverState::enter(Enemy* enemy)
{

}

void HoverState::update(Enemy* enemy, float passedTime)
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
	// - 100 to make sure martian gets on top of player
	if (player->getPositionY() < enemy->getPositionY() - 100) {
		// i will move player upwards to go up than player
		float newPosY = enemy->getPositionY() - enemy->getBaseSpeed() * passedTime;
		enemy->setPositionY(newPosY);
	}


	if (player->getPositionX() < enemy->getPositionX()) {
		float newPosX = enemy->getPositionX() - enemy->getBaseSpeed() * passedTime;
		enemy->setPositionX(newPosX);
	}
	else if (player->getPositionX() > enemy->getPositionX()) {
		float newPosX = enemy->getPositionX() + enemy->getBaseSpeed() * passedTime;
		enemy->setPositionX(newPosX);
	}

	// if my enemy gets right above the player with a good distance
	if (player->getPositionY() >= enemy->getPositionY() + 60 && abs(player->getPositionX() - enemy->getPositionX()) < 30) {
		// here i will fire the energy beam by first changing to attack state
		enemy->changeAIState(new AttackState);

	}
}

