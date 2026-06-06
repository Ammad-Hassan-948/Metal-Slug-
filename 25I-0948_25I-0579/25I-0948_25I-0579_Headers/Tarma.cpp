#include "Tarma.h"
#include "NormalState.h"

Tarma::Tarma(float startX, float startY): 
	PlayerSoldier(startX, startY, 0.0f, 0.0f, 0.6f, 64.0f, 64.0f, 0.0f, 40.0f, ColliderType::Player, 5, "Tarma")
{
	currentState = new NormalState();
	currentState->enter(this);

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Tarma.png");
	sprite.setTexture(texture);
	sprite.setScale(2, 2);

	powerUpMaxTimer = 20.0f;
	this->baseSpeed *= 0.80;          // 20% decrease in speed
	this->hp *= 0.80;       // 20% decrease in HP
	// 25% increase in vehicle fire rate
	vehicleFireRateMultipler = 1.25;
	// 20% increase in vehicle durability
	vehicleDurabilityMultiplier = 1.20;
	// player survives vehicle blast
	survivesVehicleBlast = true;

	int frames[] = { 1, 3, 2, 2, 2 };

	float timers[] = { 0.2f, 0.3f, 0.2f, 0.2f, 0.2f };


	animator = new Animator(&sprite, 5, frames, timers, 64);

	// also set the animations states

	animationRow[AnimationState::IDLE] = 0;
	animationRow[AnimationState::MOVE] = 1;
	animationRow[AnimationState::SHOOT] = 2;
	animationRow[AnimationState::SHOOT_DOWN] = 3;
	animationRow[AnimationState::SHOOT_UP] = 4;

}

void Tarma::startPowerUp()
{
	isImmune = true;
}

void Tarma::endPowerUp()
{
	isImmune = false;
}

