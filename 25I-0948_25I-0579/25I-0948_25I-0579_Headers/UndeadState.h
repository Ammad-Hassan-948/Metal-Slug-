#pragma once
#include<iostream>
#include"TransformationState.h"
#include"Soldier.h"

class UndeadState: public TransformationState
{
private:
	float timer;
public:
	UndeadState();
	void enter(Soldier* soldier)override;
	void exit(Soldier* soldier)override;
	void update(Soldier* soldier, float passedTime)override;
	void movement(Soldier* soldier, float passedTime)override;
};

