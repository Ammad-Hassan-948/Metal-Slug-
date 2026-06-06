#include "EntityManager.h"
#include"DamagableEntity.h"

void EntityManager::grow() {
	int newCapacity = capacity * 2;
	Entity** newArray = new Entity * [newCapacity];
	for (int i = 0; i < count; i++) {
		newArray[i] = entities[i];
	}

	delete[] entities;
	entities = newArray;
	capacity = newCapacity;
}


void EntityManager::add(Entity* e) {
	if (count >= capacity) {
		grow();
	}
	e->setEntityManager(this);
	entities[count] = e;
	count++;
}
void EntityManager::updateAll(float dt) {
	for (int i = 0; i < count; i++) {
		entities[i]->update(dt);
	}
}
void EntityManager::draw(sf::RenderWindow& window, Camera& cm) {
	for (int i = 0; i < count; i++) {
		if (entities[i]->getIsAlive() && entities[i]->getVisible()) {
			entities[i]->render(window, cm);
		}
		
	}
}
void EntityManager::removeDead() {

	int writeI = 0;
	for (int readI = 0; readI < count; readI++) {
		if (entities[readI]->getIsAlive()) {
			entities[writeI] = entities[readI];
			writeI++;
		}
		else {
			delete entities[readI];
		}
	}
	count = writeI;
}



int EntityManager::getCount() const {
	return count;
}
Entity* EntityManager::getEntity(int index) {
	return entities[index];
}

int EntityManager::applyExplosionDamage(float cx, float cy, float radius, float damage)
{
	int totalKills = 0;

	for (int i = 0; i < count; i++) {

		if (!entities || !entities[i]->getIsAlive()) { continue; }


		// i will get the type of entity
		int type = entities[i]->getHitbox().getType();

		// then i will procede with only those entities that take any damage
		if (type == ColliderType::Enemy || type == ColliderType::Player || type == ColliderType::Vehicle) {


			float dx = entities[i]->getPositionX() - cx;
			float dy = entities[i]->getPositionY() - cy;

			float distanceSquared = dx * dx + dy * dy;

			if (distanceSquared <= radius * radius) {

				// cast the pointer to a damageable entity pointer
				DamagableEntity* d = (DamagableEntity*)(entities[i]);

				// keep a track of hp before taking damage
				int hpBefore = d->getHp();

				// apply damage
				d->takeDamage((int)damage);

				// Now i will only consider it a multi kill if this entity was an enemy and it died now
				if (type == ColliderType::Enemy && hpBefore > 0 && d->getHp() <= 0) {
					totalKills++;
				}

			}




		}

	}

	// at the end return total kills
	return totalKills;
}

void EntityManager::clear()
{
	for (int i = 0; i < count; i++) {
		delete entities[i];
	}
	count = 0;
}



