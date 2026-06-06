#pragma once
#include"PlayerSoldier.h"

class Tarma: public PlayerSoldier
{
public:
	Tarma(float startX, float startY);
	void startPowerUp()override;
	void endPowerUp()override;
};

