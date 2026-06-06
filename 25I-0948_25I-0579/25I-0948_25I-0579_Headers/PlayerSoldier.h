#pragma once
#include<iostream>
#include"Soldier.h"

class PlayerSoldier: public Soldier
{
protected:
	int damageState;    // 0 for no damage, 1 on first hit and 2 on second and so on
	float damageTimer;        // to track time since last damage for one second part
	float powerUpTimer;
	bool powerUpActive;
	float powerUpMaxTimer;

	// i am also adding the varibales for vehicles logic here too i will use one fire rate for vehicle, one durability and one bool
	// for generalization i will set these values to 1.0f,1.0f and false and Tarma will change it 
	float vehicleFireRateMultipler;
	float vehicleDurabilityMultiplier;
	bool survivesVehicleBlast;

	// these multipliers will be used by EriKasamoto for blast radius
	float blastRadiusMultiplier;

	// for character FiolinaGermi
	float ammoMutiplier;
	float meleeDamageMultiplier;

	// i am using a static boolean developers mode to track the developer mode activation 
	static bool devMode;

public:
	PlayerSoldier(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name);
	
	// overriden function from entity class, in this i will first call the update function from soldier class and then write 
	// logic for this update as here we will need to check player states
	void update(float passedTime)override;
	void takeDamage(int amount, bool meleeAttack = false)override;
	void die()override;

    virtual void startPowerUp() {}
	virtual void endPowerUp() {}
	void activatePowerUp();
	bool isPowerUpActive() const;
	float getPowerUpTimer() const;
	
	// I have added this function to override it in MarcoRossi as he can fire in 2 directions during power ups so i will use this
	virtual void performAttack();
	// now i will add one function for special feature of eri kasamoto to throw grenade
	virtual void throwGrenade();
	float getVehicleFireRateMultiplier()const;

	int getDamageState() const;
	void resetStatus();

	static bool getDevMode();
	static void setDevMode(bool s);
};

