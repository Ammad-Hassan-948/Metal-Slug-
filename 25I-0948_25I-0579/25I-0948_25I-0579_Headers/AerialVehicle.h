#pragma once
#include"Vehicle.h"

class AerialVehicle : public Vehicle
{

protected:
	AerialVehicle(float startX, float startY, float width, float height, float gravity, int hp, const char* name);
	// this is to move the slug flying up and down in air too
	virtual void move(float dirX, float dirY, float passedTime) override = 0;
};

