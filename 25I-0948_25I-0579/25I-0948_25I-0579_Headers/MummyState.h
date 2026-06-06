#pragma once
#include<iostream>
#include"Soldier.h"
#include"TransformationState.h"

class MummyState: public TransformationState
{
private:
	float timer;
public:
	MummyState();
	void enter(Soldier* soldier)override;
	void exit(Soldier* soldier)override;
	void update(Soldier* soldier, float passedTime)override;
	void movement(Soldier* soldier, float passedTime)override;
	void attack(Soldier* soldier)override;
	void throwGrenade(Soldier* soldier)override;
};

