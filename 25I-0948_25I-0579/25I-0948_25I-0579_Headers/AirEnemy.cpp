#include "AirEnemy.h"

AirEnemy::AirEnemy(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name, PlayerSoldier* player):
	Enemy(startX, startY, velocityX, velocityY, gravity, width, height, offsetX, offsetY, colliderType, hp, name, player) {}

void AirEnemy::update(float passedTime)
{
	// i only call enemy update and no gravity
	Enemy::update(passedTime);
}
