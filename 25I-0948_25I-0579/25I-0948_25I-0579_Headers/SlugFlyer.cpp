#include "SlugFlyer.h"

SlugFlyer::SlugFlyer(float startX, float startY) : AerialVehicle(startX, startY, 128.0f, 128.0f, 0.0f, 40, "Slug Flyer") {
	baseSpeed = 300.0f;
	bulletFire = new HeavyMachineGun(-1);
	rocketLauncher = new RocketLauncher(4);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Slug Flyer.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);

	int frames[] = { 5, 5};
	float timers[] = { 0.2f, 0.1f };

	animator = new Animator(&sprite, 2, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::DIE] = 1;

	animator->setState(AnimationState::IDLE);
}

void SlugFlyer::move(float dirX, float dirY, float passedTime)
{
	positionX = this->positionX + dirX * baseSpeed * passedTime;
	positionY = this->positionY + dirY * baseSpeed * passedTime;

	if (dirX != 0) {
		direction = (dirX > 0) ? 1 : -1;
		if (animator) animator->setFlipDir(direction == -1);
	}
}

void SlugFlyer::attack()
{
	if (bulletFire != nullptr && fireRateTimer <= 0.0f) {
		float centreX = positionX + hitbox.getWidth() / 2.0f;
		float centreY = positionY + hitbox.getHeight() / 2.0f;

		bulletFire->fire(centreX, centreY, direction, aimAngle, this);


		// also reset the fire rate timer
		fireRateTimer = 0.1f;

	}
}

void SlugFlyer::secondaryAttack()
{
	if (rocketLauncher != nullptr && !rocketLauncher->weaponEmpty() && secFireRateTimer <= 0.0f) {
		float centreX = positionX + hitbox.getWidth() / 2.0f;
		float centreY = positionY + hitbox.getHeight() / 2.0f;

		rocketLauncher->fire(centreX, centreY, direction, aimAngle, this);

		// adding a longer delay for explosives
		secFireRateTimer = 0.6f;
	}
}

void SlugFlyer::setProjectileManager(ProjectileManager* pm)
{
	if (bulletFire != nullptr)
		bulletFire->setProjectileManager(pm);
	if (rocketLauncher != nullptr)
		rocketLauncher->setProjectileManager(pm);
}

