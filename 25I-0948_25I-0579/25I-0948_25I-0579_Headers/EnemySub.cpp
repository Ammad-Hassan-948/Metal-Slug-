#include "EnemySub.h"
#include "GameConstants.h"

#include"TransformationState.h"
#include"RocketLauncher.h"
#include"MartianGround.h"
#include"EntityManager.h"
#include"ParatrooperState.h"
#include"FlyingState.h"


EnemySub::EnemySub(float startX, float startY, PlayerSoldier* player) :
	AirEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 128.0f, 128.0f, 20.0f, 20.0f, ColliderType::Enemy, 7, "Flying Tara", player) {

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Enemy Sub.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);

	// edit specific attributes
	fireRate = 1.0f;
	baseSpeed = 150.0f;
	currentState = new FlyingState();
	currentState->enter(this);

	weapon = new RocketLauncher(500);
	typeId = EnemyType::ENEMY_SUB;

	int frames[] = { 2, 5, 3, 4}; 
	float timers[] = { 0.2f, 0.15f, 0.15f, 0.2f };
	animator = new Animator(&sprite, 4, frames, timers, 128);


	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::SPECIAL_1] = 1; // Turning
	animationRow[AnimationState::MOVE] = 2;
	animationRow[AnimationState::DIE] = 4;


}

void EnemySub::update(float passedTime)
{
	AirEnemy::update(passedTime);

}

void EnemySub::fireWeapon()
{
	if (weapon != nullptr && player != nullptr) {

		// first i will get the centres for the enemy and the players both for distance between their centres
		float enemyX = positionX + hitbox.getWidth() / 2;
		float enemyY = positionY + hitbox.getHeight() / 2;

		// now for player
		float playerX = player->getPositionX() + player->getHitbox().getWidth() / 2;
		float playerY = player->getPositionY() + player->getHitbox().getHeight() / 2;

		// now find the distances between their centres both x and y
		float distX = playerX - enemyX;
		float distY = playerY - enemyY;

		// now i will find the angle use atan2 which will give us exactly the angle also considering the quadrant, if we use only atan it does not consider the 
		// quadrant and only gives the angle
		float angle = atan2(-distY, distX);
		// now as this in radians to convert it into degrees
		angle *= (180.0f / 3.14159265f);

		Projectile* grenade = weapon->fire(enemyX, enemyY, direction, angle, this);

		//==============================================================================================================================================
		// here i will add this grenade to my array
	}
}

void EnemySub::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	EnemySub* enemy = new EnemySub(x, y, player);
	enemy->setProjectileManager(pm);
	mgr->add(enemy);
}


