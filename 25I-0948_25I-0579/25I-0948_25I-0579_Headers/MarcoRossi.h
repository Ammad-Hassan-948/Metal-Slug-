#pragma once
#include"PlayerSoldier.h"

class MarcoRossi: public PlayerSoldier
{
public:
	MarcoRossi(float startX, float startY);
	void performAttack()override;
};

