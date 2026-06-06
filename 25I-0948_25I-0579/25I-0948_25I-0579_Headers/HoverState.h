#pragma once
#include"EnemyAIState.h"

class HoverState : public EnemyAIState
{
private:
	float hoverTimer;
public:
	HoverState();
	void enter(Enemy* enemy)override;
	void update(Enemy* enemy, float passedTime)override;
};


