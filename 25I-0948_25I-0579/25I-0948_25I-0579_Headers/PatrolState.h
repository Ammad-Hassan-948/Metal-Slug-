#pragma once
#include"EnemyAIState.h"

class Enemy;

class PatrolState : public EnemyAIState 
{
private:
	// i am setting a timer for the enemy to patrol here and there
	float patrolTimer;
public:
	PatrolState();
	void enter(Enemy* enemy)override;
	void update(Enemy* enemy, float passedTime)override;
};

