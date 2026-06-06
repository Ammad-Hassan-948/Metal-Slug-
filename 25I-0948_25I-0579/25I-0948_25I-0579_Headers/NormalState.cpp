#pragma once
#include <SFML/Graphics.hpp>
#include "NormalState.h"
#include "Soldier.h"
#include"PlayerSoldier.h"

NormalState::NormalState() {}

void NormalState::enter(Soldier* soldier) {}

void NormalState::update(Soldier* soldier, float passedTime) {
	bool moving = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		soldier->setDirection(1);
		movement(soldier, passedTime);
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		soldier->setDirection(-1);
		soldier->getAnimator()->setFlipDir(true);
		movement(soldier, passedTime);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		jump(soldier);
	}

	bool attacked = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		soldier->performAttack();
		attacked = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		// We call throwGrenade on the soldier
		PlayerSoldier* p = (PlayerSoldier*)soldier;
		p->throwGrenade();

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		// To activate the specific power ups of players
		PlayerSoldier* p = (PlayerSoldier*)soldier;
		p->activatePowerUp();
	}


	if (!attacked) {
		if (moving)
			soldier->doAnimation(AnimationState::MOVE);
		else
			soldier->doAnimation(AnimationState::IDLE);
	}


	soldier->setPositionY(soldier->getPositionY() + soldier->getVelocityY());
}

void NormalState::movement(Soldier* soldier, float passedTime) {
	float speed = soldier->getBaseSpeed();
	soldier->setPositionX(soldier->getPositionX() + speed * soldier->getDirection());
	//soldier->getAnimator()->setFlipDir(soldier->getDirection() == -1);
}

void NormalState::handleMouse(Soldier* s, Vector2f worldPos)
{
	float cx = s->getPositionX() + s->getHitbox().getWidth() / 2.0f;
	float cy = s->getPositionY() + s->getHitbox().getHeight() / 2.0f;

	float dx = worldPos.x - cx;
	float dy = worldPos.y - cy;

	// using -dy as math coordinates and screen coordinates are different in screen 0,0 is upwards and if player is upward to enemy than 
	// difference would be negative so to shoot up we must negate dy
	float angle = atan2(-dy, dx) * 180.0f / 3.14159f;
	if (angle < 0) angle += 360.0f;

	s->setAimAngle(angle);
}

void NormalState::jump(Soldier* soldier) {
	if (soldier->getOnGround()) {
		soldier->setVelocityY(-25.0f);//setting to -20 for now to increase jump strength
		soldier->setOnGround(false);
	}
}

