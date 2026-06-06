#include "FiolinaGermi.h"
#include "NormalState.h"

FiolinaGermi::FiolinaGermi(float startX, float startY) :
	PlayerSoldier(startX, startY, 0.0f, 0.0f, 0.8f, 64.0f, 64.0f, 0.0f, 40.0f, ColliderType::Player, 5, "Fiolina Germi")
{
	currentState = new NormalState();
	currentState->enter(this);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Fiolina.png");
	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	// for 50% more ammo
	ammoMutiplier = 1.50;
	// 10% high fire rate
	fireRate *= 1.10;
	// 25% less damage on melee attack
	meleeDamageMultiplier = 0.75;
	// less grenades
	grenades -= 2;
	// power up timer
	powerUpMaxTimer = 10.0f;




	int frames[] = { 1, 3, 2, 2, 3 };

	float timers[] = { 0.2f, 0.3f, 0.2f, 0.2f, 0.3f };


	animator = new Animator(&sprite, 5, frames, timers, 64);

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::SHOOT_DOWN] = 3;
	animationRow[AnimationState::DIE] = 4;

}

void FiolinaGermi::startPowerUp()
{
	fireRate *= 2.0f;
}

void FiolinaGermi::endPowerUp()
{
	fireRate /= 2.0f;
}

