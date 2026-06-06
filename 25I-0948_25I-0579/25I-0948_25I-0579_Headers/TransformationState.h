#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Soldier;//to break circular dependency


// this class is a completely abstract class and does not need a constructor as there are no attributes and will also not need a 
// cpp file as no function will be implemented here
class TransformationState
{
	// this class will only hold certain abstract methods which further specific states will override and write logic differently
	// on the base of what different they do from the base logics
public:
	TransformationState();
	// this asks the compiler for the default destructor
	virtual ~TransformationState() = default;
	// these both functions are for the exact second when the states change and will be used to chnge the conditions according to 
	// the state
	virtual void enter(Soldier* soldier) = 0;
	// as all child classes do not use abstract.
	virtual void exit(Soldier* soldier) {}
	// I have not made my update function abstract as all classes do not use it the normal state does not use update, so it will
	// be empty by default and when any child classes writes its function it will replace it
	virtual void update(Soldier* soldier, float passedTime) {}

	// also to keep a track of mouse coordinates
	virtual void handleMouse(Soldier* s, Vector2f worldPos) {}

	// these functions are the ones which will differentiate other logic on the base of state
	virtual void movement(Soldier* soldier, float passedTime);
	virtual void attack(Soldier* soldier);
	virtual void jump(Soldier* soldier);
	virtual void throwGrenade(Soldier* soldier);
};

