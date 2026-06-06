#pragma once
#include"EnemyAIState.h"

class FlyingState : public EnemyAIState
{
private:
	float hoverTimer;
public:
	FlyingState();
	void enter(Enemy* enemy)override;
	void update(Enemy* enemy, float passedTime)override;
};


