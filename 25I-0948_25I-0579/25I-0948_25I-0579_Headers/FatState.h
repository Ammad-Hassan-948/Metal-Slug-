#pragma once
#include<iostream>
#include"TransformationState.h"
#include"Soldier.h"

class FatState: public TransformationState
{
private:
	float timer;
public:
	FatState();
	void enter(Soldier* soldier)override;
	void exit(Soldier* soldier)override;
	void update(Soldier* soldier, float passedTime)override;
};

