#pragma once
#include"Collectibles.h"

class Food : public Collectibles
{
private:
	int replenishAmmount;
public:
	Food(float posX, float posY, int replenishAmmount);
	void applyEffect(PlayerSoldier* p)override;
};


