#pragma once
#include<iostream>
#include"Entity.h"
#include"Helpers.h"
#include "Camera.h"
class DamagableEntity: public Entity
{
protected:
	char* name;
	int direction;        // 1 for right and -1 for left original sprite sheets are in right direction
	int hp;
	float aimAngle;       // as vehicles fire with a specific angle too and enemies too
	float fireRate;
public:
	DamagableEntity(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name);
	virtual ~DamagableEntity();
	int getHp()const;
	int getDirection()const;
	float getAimAngle()const;
	float getFireRate()const;
	void setDirection(int dir);
	void setAimAngle(float a);
	void setFireRate(float f);
	void render(RenderWindow& window, Camera& cam)override;
	// these two functions would be further written down on the base of what it is a character or an enemy 
	virtual void takeDamage(int amount, bool meleeAttack = false) = 0;
	virtual void die() = 0;
};

