#include "FlyingTara.h"
#include "GameConstants.h"
#include"TransformationState.h"
#include"GrenadeWeapon.h"
#include"MartianGround.h"
#include"EntityManager.h"
#include"ParatrooperState.h"
#include"FlyingState.h"


FlyingTara::FlyingTara(float startX, float startY, PlayerSoldier* player) :
	AirEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 128.0f, 128.0f, 20.0f, 20.0f, ColliderType::Enemy, 2, "Flying Tara", player) {

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Flying Tara.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);

	// edit specific attributes
	this->hp = 2;
	fireRate = 4.0f;
	baseSpeed = 150.0f;
	currentState = new FlyingState();
	currentState->enter(this);

	weapon = new GrenadeWeapon(500);
	typeId = EnemyType::FLYING_TARA;

	int frames[] = { 1, 2, 5, 2 };
	float timers[] = { 0.15f, 0.1f, 0.1f, 0.15f };
	animator = new Animator(&sprite, 4, frames, timers, 128);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SPECIAL_1] = 2; // looping maneuver
	animationRow[AnimationState::SHOOT] = 3; // Dropping bomb


}

void FlyingTara::update(float passedTime)
{
	AirEnemy::update(passedTime);

}

void FlyingTara::fireWeapon()
{
	if (weapon != nullptr) {

		float enemyX = positionX + hitbox.getWidth() / 2;
		float enemyY = positionY + hitbox.getHeight() / 2;

		float angle = 270.0f;

		Projectile* bullet = weapon->fire(enemyX, enemyY, direction, angle, this);

		
	}
}

void FlyingTara::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	int batchSize = 2;
	for (int i = 0; i < batchSize; i++) {
		FlyingTara* enemy = new FlyingTara(x + (i * 128.0f), y, player);
		enemy->setProjectileManager(pm);
		mgr->add(enemy);
	}
}


