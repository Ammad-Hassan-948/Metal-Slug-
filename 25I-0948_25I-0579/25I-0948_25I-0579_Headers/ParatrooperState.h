#pragma once
#include"EnemyAIState.h"

class Enemy;

class ParatrooperState : public EnemyAIState
{
public:
	ParatrooperState();
	void enter(Enemy* enemy)override;
	void update(Enemy* enemy, float passedTime)override;
	void exit(Enemy* enemy);
};

