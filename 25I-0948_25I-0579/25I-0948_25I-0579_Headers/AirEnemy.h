#pragma once
#include"Enemy.h"

class AirEnemy : public Enemy
{
public:
	AirEnemy(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name, PlayerSoldier* player);
	virtual ~AirEnemy() = default;
	void update(float passedTime)override;
};

