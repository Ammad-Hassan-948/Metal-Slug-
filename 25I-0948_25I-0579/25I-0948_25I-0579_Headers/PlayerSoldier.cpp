#include "PlayerSoldier.h"
#include"TransformationState.h"

// static variables are initialized globally so setting it to false initially
bool PlayerSoldier::devMode = false;

PlayerSoldier::PlayerSoldier(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name) :
	Soldier(startX, startY, velocityX, velocityY, gravity, width, height, offsetX, offsetY, colliderType, hp, name), 
	damageState(0), damageTimer(0.0f), powerUpTimer(0.0f), powerUpActive(false), vehicleFireRateMultipler(1.0f), 
	vehicleDurabilityMultiplier(1.0f), survivesVehicleBlast(false), ammoMutiplier(1.0f), blastRadiusMultiplier(1.0f),
	meleeDamageMultiplier(1.0f) { 
	
	playerEntity = true;
}

void PlayerSoldier::update(float passedTime)
{
	Soldier::update(passedTime);

	// now for specific player logic i will check for the damage state in every update call
	if (damageState > 0) {
		damageTimer -= passedTime;

		if (damageTimer <= 0.0f) {
			damageState = 0;
		}
	}

	// now also add the power up logic here as every player has a power up for a specific time
	if (powerUpActive) {
		powerUpTimer -= passedTime;

		// if time is over
		if (powerUpTimer <= 0.0f) {
			powerUpActive = false;

			// also call the end power up function to go back to the original steps if our power up has changed anything
			endPowerUp();
		}
	
	}
}

void PlayerSoldier::takeDamage(int amount, bool meleeAttack)
{
	if (devMode)
		return;

	// if the power up is active and is immue is true the player will not take any damage
	if (powerUpActive && isImmune)
		return;

	// else normal logic for state change
	// for take damage implementation i would check the state of player and implement on basis of it
	damageState++;
	damageTimer = 1.0f;

	if (damageState > 2) {
		die();
	}
}

void PlayerSoldier::die()
{
	isAlive = false;
}

void PlayerSoldier::activatePowerUp()
{
	if (!powerUpActive) {
		powerUpActive = true;
		powerUpTimer = powerUpMaxTimer;

		// also call the start function here incase our character has overriden the function for starting power up
		startPowerUp();
	}
}

bool PlayerSoldier::isPowerUpActive() const
{
	return powerUpActive;
}

float PlayerSoldier::getPowerUpTimer() const
{
	return powerUpTimer;
}

void PlayerSoldier::performAttack()
{
	if (currentState != nullptr)
		currentState->attack(this);
}

void PlayerSoldier::throwGrenade()
{
	if (currentState != nullptr) {
		// use current state to call throw grenade fucntion
		currentState->throwGrenade(this);
	}
}

float PlayerSoldier::getVehicleFireRateMultiplier() const
{
	return vehicleFireRateMultipler;
}

int PlayerSoldier::getDamageState() const
{
	return damageState;
}

void PlayerSoldier::resetStatus()
{
	isAlive = true;
	damageState = 0;
	damageTimer = 0.0f;
	hp = 5;
}

bool PlayerSoldier::getDevMode()
{
	return devMode;
}

void PlayerSoldier::setDevMode(bool s)
{
	devMode = s;
}



