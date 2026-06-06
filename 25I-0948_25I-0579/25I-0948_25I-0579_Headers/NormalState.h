#pragma once
#include<iostream>
#include"TransformationState.h"

class NormalState: public TransformationState
{
public:
	NormalState();
	void enter(Soldier* soldier) override;
	void update(Soldier* soldier, float passedTime) override;
	void movement(Soldier* soldier, float passedTime) override;
	void jump(Soldier* soldier) override;
	void handleMouse(Soldier* s, Vector2f worldPos);
};

