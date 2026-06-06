#pragma once
#include"Vehicle.h"

class AquaticVehicle : public Vehicle
{
public:
	AquaticVehicle(float startX, float startY, float width, float height, float gravity, int hp, const char* name);
	// this is to move the slug flying up and down in air too
	virtual void move(float dirX, float dirY, float passedTime) override = 0;
};

