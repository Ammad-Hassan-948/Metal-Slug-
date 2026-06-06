#pragma once
#include"EnemyAIState.h"

class ApproachState : public EnemyAIState
{
public:
	ApproachState();
	void enter(Enemy* enemy)override;
	void update(Enemy* enemy, float passedTime);
};

