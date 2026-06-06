#include "MetalSlug.h"
#include"Weapon.h"
#include"HeavyMachineGun.h"
#include"RocketLauncher.h"

MetalSlug::MetalSlug(float startX, float startY) : GroundVehicle(startX, startY, 128.0f, 128.0f, 0.6f, 40, "Metal Slug") {
	baseSpeed = 150.0f;
	bulletFire = new HeavyMachineGun(-1);
	explosiveFire = new RocketLauncher(10);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Metal Tank.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);


	int frames[] = { 1, 2, 2, 3}; 
	float timers[] = { 0.2f, 0.15f, 0.1f, 0.1f };

	animator = new Animator(&sprite, 4, frames, timers, 128);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 0;
	animationRow[AnimationState::SHOOT] = 1;
	animationRow[AnimationState::DIE] = 2;
}

MetalSlug::~MetalSlug()
{
	if (bulletFire != nullptr)
		delete bulletFire;

	if (explosiveFire != nullptr)
		delete explosiveFire;
}

void MetalSlug::move(float dirX, float dirY, float passedTime)
{
	positionX = this->positionX + dirX * baseSpeed * passedTime;

	if (dirX != 0) {
		direction = (dirX > 0) ? 1 : -1;
		if (animator) animator->setFlipDir(direction == -1);
		doAnimation(AnimationState::MOVE);
	}
	else {
		doAnimation(AnimationState::IDLE);
	}
}

void MetalSlug::attack()
{
	if (bulletFire != nullptr && fireRateTimer <= 0.0f) {
		float centreX = positionX + hitbox.getWidth() / 2.0f;
		float centreY = positionY + hitbox.getHeight() / 2.0f;

		// simply call fire function on weapon
		bulletFire->fire(centreX, centreY, direction, aimAngle, this);
        
		doAnimation(AnimationState::SHOOT);

		// also reset the fire rate timer
		fireRateTimer = 0.1f;

	}
}

void MetalSlug::secondaryAttack()
{
	if (explosiveFire != nullptr && secFireRateTimer <= 0.0f) {
		float centreX = positionX + hitbox.getWidth() / 2.0f;
		float centreY = positionY + hitbox.getHeight() / 2.0f;

		explosiveFire->fire(centreX, centreY, direction, aimAngle, this);

		doAnimation(AnimationState::SHOOT);

		secFireRateTimer = 0.6f;
	}
}

void MetalSlug::jump()
{
	if (onGround) {
		setVelocityY(-15.0f);
		onGround = false;
	}
}

void MetalSlug::setProjectileManager(ProjectileManager* pm)
{
	if (bulletFire != nullptr)
		bulletFire->setProjectileManager(pm);
	if (explosiveFire != nullptr)
		explosiveFire->setProjectileManager(pm);
}



