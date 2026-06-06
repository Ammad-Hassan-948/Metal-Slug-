#include "UndeadState.h"
#include"NormalState.h"

UndeadState::UndeadState()
{
	timer = 10.0f;
}

void UndeadState::enter(Soldier* soldier)
{
	// i will add logic to change the animation if i add one 
	//==================================================================================================================
}

void UndeadState::exit(Soldier* soldier)
{
	// add logic to change sprite sheets back
	//===================================================================================================================
}

void UndeadState::update(Soldier* soldier, float passedTime)
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
		// undead cannot jump as high or at all? 
		// but let's keep it for gameplay
		if (soldier->getOnGround()) {
			soldier->setVelocityY(-10.0f);
			soldier->setOnGround(false);
		}
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

void UndeadState::movement(Soldier* soldier, float passedTime)
{
	// as undead walks slower 50%
	float decSpead = soldier->getBaseSpeed() * 0.5;

	float newPosX = soldier->getPositionX() + (soldier->getDirection() * decSpead);
	soldier->setPositionX(newPosX);
}



