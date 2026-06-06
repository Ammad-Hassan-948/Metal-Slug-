#pragma once

#include"EnemyAIState.h"


class AttackState : public EnemyAIState
{
private:
	// for attack cooldown to stop firing bullets every frame
	float coolDownTime;
	// a counter to track the shooting animation time of the enemy
	float attackAnimationTimer;
public:
	AttackState();
	void enter(Enemy* enemy)override;
	void update(Enemy* enemy, float passedTime)override;
};

