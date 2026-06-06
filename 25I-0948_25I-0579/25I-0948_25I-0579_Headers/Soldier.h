#pragma once
#include<iostream>
#include"Collider.h"
#include"DamagableEntity.h"
#include"Helpers.h"
#include "Camera.h"

using namespace sf;

class TransformationState;

class Weapon;

class ProjectileManager;

class Soldier : public DamagableEntity 
{
protected:
	TransformationState* currentState;
	Weapon* currentWeapon;
	Weapon* melee;
	Weapon* specialWeapon;
	Weapon* pistol;
	int lives;
	int grenades;
	int saturation;
	float fireRateTimer;
	// a manager for projectiles to pass it to new weapons
	ProjectileManager* projMgr;
	// a bool to check Tarma's power state where he becomes immune to all damage for 20 seconds 
	bool isImmune;
public:
	Soldier(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name);
	virtual ~Soldier();
	float getBaseSpeed()const;
	Weapon* getCurrentWeapon()const;
	Weapon* getSpecialWeapon()const;
	Weapon* getPistol()const;
	Weapon* getMelee()const;
	int getGrenades();
	int getLives() const;
	void setLives(int l);
	void setPistol(Weapon* p);
	void setCurrentWeapon(Weapon* changed);
	void addGrenades(int g);
	void setGrenades(int s);
	void addSaturation(int s);
	void changeState(TransformationState* newState);
	void equipWeapon(Weapon* newWeapon);
	void setProjectileManager(ProjectileManager* pm);
	float getFireRateTimer() const;
	void setFireRateTimer(float t);
	// overriden function from entity class
	void update(float passedTime)override;
	// also adding the virtual functions
	virtual void takeDamage(int amount, bool meleeAttack = false) = 0;
	virtual void die() = 0;
	virtual void performAttack() = 0;

	ProjectileManager* getProjectileManager()const;


	// also to keep a track of mouse
	void handleMouse(Vector2f worldPosition);

	//ammad
	void setFireRate(float f);
	float getfireRate() const;
	void render(RenderWindow& window, Camera& cam)override;
};

