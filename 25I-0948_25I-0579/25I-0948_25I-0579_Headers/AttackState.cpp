#include "AttackState.h"
#include"PatrolState.h"
#include"EnemyAIState.h"
#include"Enemy.h"

AttackState::AttackState(): coolDownTime(0.0f), attackAnimationTimer(0.0f) { }



void AttackState::enter(Enemy* enemy)
{
	// here i will just stop the enemy from moving so that he remains still while shooting
	enemy->setVelocityX(0.0f);

	// randomize initial cooldown so they don't all fire at once
	coolDownTime = (float)(rand() % 100) / 100.0f;

	//enemy->doAnimation(SHOOT);
}

void AttackState::update(Enemy* enemy, float passedTime)
{
	coolDownTime -= passedTime;
	attackAnimationTimer -= passedTime;

	// if the timer for attack animation has ended as we have set our 5 frames for only one second
	if (attackAnimationTimer <= 0.0f) {
		// so we set our animation back to idle state for that instant
		enemy->doAnimation(AnimationState::IDLE);
	}

	// now i will check if i have my gun reloaded and its cooldown is over
	if (coolDownTime <= 0.0f) {

		// here now i will shoot again if player is in range
		if (enemy->playerInRange(600.0f)) {

			enemy->fireWeapon();
			enemy->doAnimation(AnimationState::SHOOT);

			// now find perfect cool down for fire rate
			coolDownTime = 1.0f / enemy->getFireRate();

			// also set the timer for animation
			attackAnimationTimer = 1.0f;
		}
		else {
			// this means the player has left our range so move back to patrol state
			enemy->changeAIState(new PatrolState());
		}
	}
}
