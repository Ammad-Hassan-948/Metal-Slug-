#pragma once
#include"PlayerSoldier.h"

class FiolinaGermi : public PlayerSoldier
{
public:
	FiolinaGermi(float startX, float startY);
	void startPowerUp()override;
	void endPowerUp()override;
};

