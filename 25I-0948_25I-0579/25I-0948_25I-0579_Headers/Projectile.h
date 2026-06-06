#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Camera.h"
#include "Collider.h"

#include"DamagableEntity.h"

class EntityManager;
class ExplosionBehavior;

class Projectile : public Entity {
protected:
	bool isPlayerOwned;
	float angle;
	bool active;
	float projectileTimer;
	float damageInflicted;
	//float baseSpeed;

	ExplosionBehavior* explosion;

	EntityManager* entityManager;

public:
	Projectile(float x, float y, float angle, float damage, int t,
		float w, float h, ExplosionBehavior* expl = nullptr);

	virtual ~Projectile();

	virtual void update(float dt) = 0;
	virtual void onHit(Entity* target) = 0;

	virtual void render(sf::RenderWindow& window, Camera& cam);

	bool isActive()const;
	bool isDead() const;

	float getDamage() const { return damageInflicted; }

	void deactivate() { active = false; }




	bool getIsPlayerOwned() const { return isPlayerOwned; }

	void setEntityManager(EntityManager* manager) { entityManager = manager; }

	// to know their type
	virtual bool isLaser() const { return false; }

	virtual bool isBallistic() const { return false; }




	


};



