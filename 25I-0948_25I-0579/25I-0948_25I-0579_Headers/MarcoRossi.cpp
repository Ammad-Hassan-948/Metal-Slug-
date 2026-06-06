#include "MarcoRossi.h"
#include"NormalState.h"
#include"Weapon.h"

MarcoRossi::MarcoRossi(float startX, float startY) :
	PlayerSoldier(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 0.0f, 40.0f, ColliderType::Player, 5, "Marco Rossi") {

	fireRate = 1.25f;
	grenades -= 2;
	// set the max time for power up for marco to 10
	powerUpMaxTimer = 10.0f;

	currentState = new NormalState();
	currentState->enter(this);

	
	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Marco Rossi.png");
	sprite.setTexture(texture);
	sprite.setScale(2,2);

	int frames[] = { 1, 3, 4, 5, 2, 2 };

	float timers[] = { 0.2f, 0.15f, 0.1f, 0.08f, 0.1f, 0.1f };

	animator = new Animator(&sprite, 6, frames, timers, 64);

	// also set the animation rows
	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::MELEE] = 3;
	animationRow[AnimationState::SHOOT_UP] = 4;
	animationRow[AnimationState::SHOOT_DOWN] = 5;

}

void MarcoRossi::performAttack()
{
	// First i am going to check if this can actually fire or not due to timer
	bool canFire = (currentWeapon != nullptr && fireRateTimer <= 0.0f);

	// in this i will first perform the normal attack in same direction
	PlayerSoldier::performAttack();

	// then i will check for power up if it is active then i would also fire in opposite direction
	if (powerUpActive && canFire && currentWeapon != nullptr) {

		// reverse the current direction
		direction = -direction;

		// find centre for firing
		float cX = positionX + hitbox.getWidth() / 2.0f;
		float cY = positionY + hitbox.getHeight() / 2.0f;

		// I am going to use the aim angle but as player has to fire from 0 to 90
		float angle = aimAngle;

		if (direction == 1) { // when facing right

			if (angle > 90.0f && angle <= 270.0f) 
				angle = 90.0f;
			else if (angle > 270.0f) 
				angle = 0.0f;
		}
		else { // when facing left
			if (angle < 90.0f || angle > 270.0f) 
				angle = 90.0f;
			else if (angle > 180.0f && angle <= 270.0f) 
				angle = 180.0f;
		}

		// here i will fire forcibly calling the fire function of weapon
		currentWeapon->fire(cX, cY, direction, angle, this);

		// reverse direction bakwards to restore original
		direction = -direction;
	}
}

