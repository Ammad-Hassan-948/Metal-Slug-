#include "GroundEnemy.h"
#include"EnemyAIState.h"

GroundEnemy::GroundEnemy(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name, PlayerSoldier* player):
	Enemy(startX, startY, velocityX, velocityY, gravity, width, height, offsetX, offsetY, colliderType, hp, name, player), isParatrooper(false) { }

void GroundEnemy::update(float passedTime)
{
	if (!isParatrooper) {
		// first apply gravity
		applyGravity();

		// Update vertical position based on velocityY
		positionY += velocityY;
	}

	// here i will now call the update function of enemy to change the states etc 
	Enemy::update(passedTime);

}

void GroundEnemy::setIsParatrooper(bool p)
{
	isParatrooper = p;
}

bool GroundEnemy::getIsParatrooper() const
{
	return isParatrooper;
}

