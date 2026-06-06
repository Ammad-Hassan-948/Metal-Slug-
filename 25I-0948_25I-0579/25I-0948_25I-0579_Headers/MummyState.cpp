#include "MummyState.h"
#include"NormalState.h"

MummyState::MummyState()
{
	timer = 10.0f;
}

void MummyState::enter(Soldier* soldier)
{
	// when player turns into mummy he can only use the knife 
	soldier->setCurrentWeapon(soldier->getMelee());
}

void MummyState::exit(Soldier* soldier)
{
	if (soldier->getSpecialWeapon() != nullptr) {
		soldier->setCurrentWeapon(soldier->getSpecialWeapon());
	}
	else {
		soldier->setCurrentWeapon(soldier->getPistol());
	}
}

void MummyState::update(Soldier* soldier, float passedTime)
{
	timer -= passedTime;

	if (timer <= 0) {
		soldier->changeState(new NormalState());
		return;
	}

	bool moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		soldier->setDirection(1);
		movement(soldier, passedTime);
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		soldier->setDirection(-1);
		movement(soldier, passedTime);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		jump(soldier);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		soldier->performAttack();
	}

	if (moving)
		soldier->doAnimation(AnimationState::MOVE);
	else
		soldier->doAnimation(AnimationState::IDLE);

	soldier->setPositionY(soldier->getPositionY() + soldier->getVelocityY());
}

void MummyState::movement(Soldier* soldier, float passedTime)
{
	// I am decreasing speed of mummy a litle too to show difference along with weapon
	float decSpead = soldier->getBaseSpeed() * 0.8;

	float newPosX = soldier->getPositionX() + (soldier->getDirection() * decSpead);
	soldier->setPositionX(newPosX);
	
}

void MummyState::attack(Soldier* soldier)
{
	//================================================================================================================
	// will call fire function later
	soldier->getCurrentWeapon();
}

void MummyState::throwGrenade(Soldier* soldier)
{
	// i am putting it empty to show no implementation and throw no grenade when state is mummy
	return;
}

