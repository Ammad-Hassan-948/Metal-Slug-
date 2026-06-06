#include"Soldier.h"
#include "TransformationState.h"
#include"Weapon.h"
#include"ProjectileManager.h"

class Soldier;
TransformationState::TransformationState()
{
}

void TransformationState::movement(Soldier* soldier, float passedTime)
{
	// I have multiplied the speed by passed time as if i simply keep adding the movement will depend on how many cycle my game loop is going in 1 seconds but
	// if i mul by passed time this ensures that it will remain constant
	float newPosX = soldier->getPositionX() + (soldier->getDirection() * soldier->getBaseSpeed() * passedTime);
	soldier->setPositionX(newPosX);

	soldier->doAnimation(AnimationState::MOVE);
}

void TransformationState::attack(Soldier* soldier)
{
	if (soldier->getCurrentWeapon() != nullptr && soldier->getFireRateTimer() <= 0.0f) {
		float sx = soldier->getPositionX() + soldier->getHitbox().getWidth() / 2.0f;
		float sy = soldier->getPositionY() + soldier->getHitbox().getHeight() / 2.0f;

		// Use the aim angle which is updated by the mouse
		float angle = soldier->getAimAngle();

		// To restrict the angle between 0 and 90 in both directions
		if (soldier->getDirection() == 1) { // When facing right
			if (angle > 90.0f && angle <= 270.0f) angle = 90.0f;
			else if (angle > 270.0f) angle = 0.0f;
		}
		else { // when facing left
			if (angle < 90.0f || angle > 270.0f) angle = 90.0f;
			else if (angle > 180.0f && angle <= 270.0f) angle = 180.0f;
		}

		soldier->getCurrentWeapon()->fire(sx, sy, soldier->getDirection(), angle, soldier);

		// resetting the timer to 1/ fire rate also applying soldier fireRate for fiolinas power up
		soldier->setFireRateTimer(1.0f / (soldier->getCurrentWeapon()->getFireRate() * soldier->getfireRate()));

		soldier->doAnimation(AnimationState::SHOOT);
	}
}



void TransformationState::jump(Soldier* soldier)
{
	// for jump i just have to set some vertical velocity to go up and change the bool onGround to false if player is on ground
	if (soldier->getOnGround()) {
		soldier->setVelocityY(-15.0f);
		soldier->setPositionY(soldier->getPositionY() - 1.0f);
		soldier->setOnGround(false);
	}
	
}

void TransformationState::throwGrenade(Soldier* soldier)
{
	if (soldier->getGrenades() > 0 && soldier->getFireRateTimer() <= 0.0f) {

		soldier->doAnimation(AnimationState::THROW_GRENADE);

		// first decrease no of grenades
		soldier->setGrenades(soldier->getGrenades() - 1);

		// find centre
		float cx = soldier->getPositionX() + soldier->getHitbox().getWidth() / 2.0f;
		float cy = soldier->getPositionY() + soldier->getHitbox().getHeight() / 2.0f;

		// Determine velocity based on direction
		float vx = (soldier->getDirection() == 1) ? 400.0f : -400.0f;
		float vy = -600.0f; // Give a small vertical velocity
		
       // Use the ProjectileManager to spawn the hand grenade
		if (soldier->getProjectileManager() != nullptr) {
			soldier->getProjectileManager()->spawnHandGrenade(cx, cy, vx, vy, ColliderType::PlayerBullet);

		}
		
		// set cooldown again
		soldier->setFireRateTimer(0.5f);


		
	}
}

