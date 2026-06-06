#pragma once
#include"Collectibles.h"
class Weapon;

class SupplyCrate : public Collectibles
{
private:
	Weapon* storedWeapon;
	int grenadeCount;
	int ammoCount;
public:
	SupplyCrate(float posX, float posY);
	~SupplyCrate();
	bool needsInput()const override;
	void replenishAmmo(PlayerSoldier* p);
	void applyEffect(PlayerSoldier* p);
};


