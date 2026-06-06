#pragma once



class Enemy;

class EnemyAIState
{
public:
	// a virtual destructor and ask the compiler for default as there are no dynamic memory
	virtual ~EnemyAIState() = default;
	// a function to enter specific states which would be absract as each state will change depending on its own
	virtual void enter(Enemy* enemy) = 0;
	// an update function this too abstract so each state has its own update function
	virtual void update(Enemy* enemy, float passedTime) = 0;
	// exit function to go back to initial conditions
	virtual void exit(Enemy* enemy) {};
};

