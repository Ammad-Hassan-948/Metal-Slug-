#pragma once
#include"GroundVehicle.h"

class Weapon;

class MetalSlug : public GroundVehicle
{
private:
	Weapon* bulletFire;
	Weapon* explosiveFire;
public:
	MetalSlug(float startX, float startY);
	~MetalSlug()override;
	void move(float dirX, float dirY, float passedTime) override;
	void attack()override;
	void secondaryAttack()override;
	void jump()override;
	void setProjectileManager(ProjectileManager* pm);


};


