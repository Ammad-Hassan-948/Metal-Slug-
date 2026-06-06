#pragma once
#include"Enemy.h"

class GroundEnemy : public Enemy
{
protected:
	bool isParatrooper;
public:
	GroundEnemy(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name, PlayerSoldier* player);
	virtual ~GroundEnemy() = default;
	// here gravity will be introduced in the update function
	void update(float passedTime)override;
	void setIsParatrooper(bool p)override;
	bool getIsParatrooper()const override;
};

