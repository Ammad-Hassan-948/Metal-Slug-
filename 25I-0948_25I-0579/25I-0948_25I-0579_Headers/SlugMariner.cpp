#include "SlugMariner.h"
#include"SlugMariner.h"
#include"HeavyMachineGun.h"

SlugMariner::SlugMariner(float startX, float startY) : AquaticVehicle(startX, startY, 128.0f, 128.0f, 0.0f, 40, "Slug Mariner"),
horizontal(3), vertical(3), projectile(3) {
	baseSpeed = 150.0f;
	rocketLauncher = new RocketLauncher(100);
	bulletFire = new HeavyMachineGun(-1);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Enemy Sub.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);


	int frames[] = { 2, 5, 3, 4 };

	float timers[] = { 0.2f, 0.12f, 0.2f, 0.2f };

	animator = new Animator(&sprite, 4, frames, timers, 128);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::SPECIAL_1] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::MOVE] = 2;
	animationRow[AnimationState::DIE] = 3;

}

void SlugMariner::move(float dirX, float dirY, float passedTime)
{
	positionX = this->positionX + dirX * baseSpeed * passedTime;
	positionY = this->positionY + dirY * baseSpeed * passedTime;

	if (dirX != 0) {
		direction = (dirX > 0) ? 1 : -1;
		if (animator) animator->setFlipDir(direction == -1);
	}
}

void SlugMariner::attack()
{
	if (bulletFire != nullptr && fireRateTimer <= 0.0f) {
		float centreX = positionX + hitbox.getWidth() / 2.0f;
		float centreY = positionY + hitbox.getHeight() / 2.0f;

		bulletFire->fire(centreX, centreY, direction, aimAngle, this);

		// also reset the fire rate timer
		fireRateTimer = 0.1f;

	}
}

void SlugMariner::secondaryAttack()
{
	if (fireRateTimer >= 0.0f)
		return;

	float centreX = positionX + hitbox.getWidth() / 2.0f;
	float centreY = positionY + hitbox.getHeight() / 2.0f;

	bool fired = false;

	if (horizontal > 0) {

		float angle = (direction == 1) ? 0.0f : 180.0f;
		rocketLauncher->fire(centreX, centreY, direction, angle, this);
		horizontal--;

		// if vehicle fired simply turn the bool on
		fired = true;
	}
	else if (vertical > 0) {

		rocketLauncher->fire(centreX, centreY, direction, -90.0f, this);
		vertical--;

		fired = true;
	}
	else if (projectile > 0) {

		rocketLauncher->fire(centreX, centreY, direction, aimAngle, this);
		projectile--;

		fired = true;
	}

	if (fired)    // set the fire rate timer
		fireRateTimer = 0.6f;
}

void SlugMariner::setProjectileManager(ProjectileManager* pm)
{
	if (bulletFire != nullptr)
		bulletFire->setProjectileManager(pm);
	if (rocketLauncher != nullptr)
		rocketLauncher->setProjectileManager(pm);
}

