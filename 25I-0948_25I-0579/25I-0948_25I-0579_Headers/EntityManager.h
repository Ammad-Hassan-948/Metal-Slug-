#pragma once

#include "Entity.h"
#include "Camera.h"

class EntityManager {

	Entity** entities;
	int count;
	int capacity;

	void grow();

public:

	EntityManager() {
		capacity = 16;
		count = 0;
		entities = new Entity * [capacity];
	}
	~EntityManager() {
		for (int i = 0; i < count; i++) {
			delete entities[i];
		}
		delete[] entities;
	}

	void add(Entity* e);
	void updateAll(float dt);
	//void draw()
	void draw(sf::RenderWindow& window, Camera& cm);
	void removeDead();
	int getCount() const;
	Entity* getEntity(int index);
	//void applyExplosionDamage(float cx, float cy, float radius, float damage);
	void clear();





	//bool isPlayer();
	int applyExplosionDamage(float cx, float cy, float radius, float damage);
};
