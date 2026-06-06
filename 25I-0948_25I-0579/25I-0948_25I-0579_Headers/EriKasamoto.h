#pragma once
#include"PlayerSoldier.h"

class EriKasamoto: public PlayerSoldier
{
public:
	EriKasamoto(float startX, float startY);
	void throwGrenade()override;
};

