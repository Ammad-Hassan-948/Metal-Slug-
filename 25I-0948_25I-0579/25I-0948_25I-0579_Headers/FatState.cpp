#include "FatState.h"
#include"NormalState.h"

FatState::FatState()
{
	timer = 60.0f;
}

void FatState::enter(Soldier* soldier)
{
	//================================================================================================================
	// here change the sprite later
}

void FatState::exit(Soldier* soldier)
{
	//================================================================================================================
	// change state later back and saturation = 0
}

void FatState::update(Soldier* soldier, float passedTime)
{
	timer -= passedTime;

	if (timer <= 0) {
		soldier->changeState(new NormalState());
	}
}


