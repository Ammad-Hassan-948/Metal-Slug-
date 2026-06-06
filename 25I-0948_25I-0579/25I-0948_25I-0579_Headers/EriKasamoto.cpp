#include "EriKasamoto.h"
#include "NormalState.h"
#include"ProjectileManager.h"

EriKasamoto::EriKasamoto(float startX, float startY):
	PlayerSoldier(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 0.0f, 40.0f, ColliderType::Player, 5, "Eri Kasamoto")
{
	currentState = new NormalState();
	currentState->enter(this);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Eri Kasamoto.png");
	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	// first double grenades
	grenades *= 2;
	// for bigger blast radius
	blastRadiusMultiplier = 1.5f;
	// reduced fire rate
	fireRate *= 0.8f;
	// set timer for power up
	powerUpMaxTimer = 10.0f;
	// also delete the melee as it cannot use
	delete melee;
	melee = nullptr;

	int frames[] = { 1, 2, 2, 2, 2 };

	float timers[] = { 0.2f, 0.3f, 0.3f, 0.3f, 0.3f };


	animator = new Animator(&sprite, 5, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::SHOOT_UP] = 3;
	animationRow[AnimationState::SHOOT_DOWN] = 4;

}

void EriKasamoto::throwGrenade()
{
	// first check if we can actually throw a grenade
	bool canThrow = (grenades > 0 && fireRateTimer <= 0.0f);

	// here i will first call the simple PlayerSoldier function for it
	if (currentState != nullptr) {

		PlayerSoldier::throwGrenade();

		// here i will now spawn another grenade if power up is active and we actually threw one
		if (powerUpActive && canThrow) {

			// here i will spawn the second grenade with a different velocity
			// find centre
			float centreX = positionX + hitbox.getWidth() / 2.0f;
			float centreY = positionY + hitbox.getHeight() / 2.0f;

			// Determine velocity based on direction - second grenade goes further
			float vx = (direction == 1) ? 550.0f : -550.0f;
			float vy = -750.0f;

			// Use the ProjectileManager to spawn the hand grenade
			if (projMgr != nullptr) {
				projMgr->spawnHandGrenade(centreX, centreY, vx, vy, ColliderType::PlayerBullet);
			}
		}

	}
}

