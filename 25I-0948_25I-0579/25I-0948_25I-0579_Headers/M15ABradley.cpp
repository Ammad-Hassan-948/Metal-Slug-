#include "M15ABradley.h"
#include "GameConstants.h"
#include"EntityManager.h"
#include"ApproachState.h"
#include<iostream>
#include"RocketLauncher.h"
#include<cmath>

using namespace std;

M15ABradley::M15ABradley(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 128.0f, 128.0f, 0.0f, 40.0f, ColliderType::Enemy, 7, "M-15A Bradley", player) {

	typeId = EnemyType::M15A_BRADLEY;
	fireRate = 0.5f;
	baseSpeed = 150.0f;
	currentState = new ApproachState();
	currentState->enter(this);

	weapon = new RocketLauncher(-1);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/M-15A.png");
	sprite.setTexture(texture);
	sprite.setScale(1.0f, 1.0f);

	int frames[] = { 2, 3, 2, 4 }; 
	float timers[] = { 0.2f, 0.15f, 0.15f, 0.2f };
	animator = new Animator(&sprite, 4, frames, timers, 128);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 0; 
	animationRow[AnimationState::SHOOT_UP] = 1;
	animationRow[AnimationState::DIE] = 2;
	animationRow[AnimationState::SPECIAL_1] = 3;

}

void M15ABradley::fireWeapon()
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

void M15ABradley::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	
	M15ABradley* enemy = new M15ABradley(x + 128.0f, y, player);
	enemy->setProjectileManager(pm);
	mgr->add(enemy);
	
}



