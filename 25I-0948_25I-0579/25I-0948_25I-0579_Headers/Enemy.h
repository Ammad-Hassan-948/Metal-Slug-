#pragma once
#include<iostream>

#include"DamagableEntity.h"
#include"PlayerSoldier.h"

class Projectile;

class EnemyAIState;

class ProjectileManager;

class Enemy : public DamagableEntity
{
protected:
	// pointer to the current enemy AI state
	EnemyAIState* currentState;
	// to change states i am keeping a pointer to save the old state
	EnemyAIState* oldState;
	PlayerSoldier* player;
	Weapon* weapon;
	// to determine batch of each soldier
	int batchSize;
	class Boss* parentBoss;
	int typeId;
	bool killedByMelee;

	int baseScore;
public:
	Enemy(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name, PlayerSoldier* player);
	virtual ~Enemy();
	PlayerSoldier* getPlayer()const;
	void setParentBoss(class Boss* b) { parentBoss = b; }
	void changeAIState(EnemyAIState* newState);
	void update(float passedTime)override;
	virtual bool playerInRange(float threshholdX);
	// this will be overriden by every child to tell how they fire
	virtual void fireWeapon();
	virtual void takeDamage(int amount, bool meleeAttack = false)override;
	virtual void die()override;
	// writing empty here so that i can override and use in ground enemy and it is accessible from enemy pointer
	virtual void setIsParatrooper(bool p) {}
	void setPlayer(PlayerSoldier* p)override;
	virtual bool getIsParatrooper()const;
	void setProjectileManager(ProjectileManager* pm);
	int getEnemyTypeId() const { return typeId; }
};

