#pragma once
#include"Vehicle.h"

class GroundVehicle : public Vehicle
{
protected:
	GroundVehicle(float startX, float startY, float width, float height, float gravity, int hp, const char* name);
	virtual void jump() = 0;
	virtual void update(float passedTime)override;
};

