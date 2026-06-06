#include "MartianGround.h"
#include "GameConstants.h"
#include"PatrolState.h"
#include"Collider.h"
#include<iostream>
#include"Pistol.h"
#include"EntityManager.h"

MartianGround::MartianGround(float startX, float startY, PlayerSoldier* player) :
	GroundEnemy(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 20.0f, 20.0f, ColliderType::Enemy, 3, "Martian", player) {

	// edit specific attributes
	fireRate = 4.0f;
	baseSpeed = 150.0f;
	currentState = new PatrolState();
	currentState->enter(this);


	weapon = new Pistol(500);
	typeId = EnemyType::MARTIAN;

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Martian.png");
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);


	int frames[] = { 4, 2, 4, 4, 5, 6 };
	float timers[] = { 0.15f, 0.1f, 0.2f, 0.15f, 0.15f, 0.15f };
	animator = new Animator(&sprite, 6, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 2;
	animationRow[AnimationState::MOVE] = 3;
	animationRow[AnimationState::SHOOT] = 4;
	animationRow[AnimationState::DIE] = 5;


}

void MartianGround::fireWeapon()
{
	if (weapon != nullptr && player != nullptr) {

		float enemyX = positionX + hitbox.getWidth() / 2;
		float enemyY = positionY + hitbox.getHeight() / 2;

		// calculate the angle to shoot the player
		float dx = player->getPositionX() - enemyX;
		float dy = player->getPositionY() - enemyY;
		float angle = atan2(-dy, dx) * 180.0f / 3.14159f;

		weapon->fire(enemyX, enemyY, direction, angle, this);

		// shoot animation
		doAnimation(AnimationState::SHOOT);
	}
}

void MartianGround::spawn(float x, float y, PlayerSoldier* player, EntityManager* mgr, ProjectileManager* pm)
{
	
	MartianGround* enemy = new MartianGround(x + 40.0f, y, player);
	enemy->setProjectileManager(pm);
	mgr->add(enemy);
	
}


