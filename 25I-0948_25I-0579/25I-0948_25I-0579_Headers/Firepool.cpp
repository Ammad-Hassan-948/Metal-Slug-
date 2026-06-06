#include "FirePool.h"
#include <cmath>
#include"DamagableEntity.h"

using namespace sf;

static const float FIRE_TEXTURE_SIZE = 128.0f;

FirePool::FirePool(float cx, float cy, float radius, float damagePerSec, float duration) :

	Entity(cx - radius, cy - radius, 0.0f, 0.0f, 0.6f,
		radius * 2.0f, radius * 2.0f//width and height as diameter
		, 0.0f, 0.0f, ColliderType::FirePool),
	radius(radius), damagePerSec(damagePerSec), duration(duration), elapsed(0.0f), tickTimer(0.0f),
	dead(false)
{

	fireTexture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Fire Bomb Explosive.png");
	fireSprite.setTexture(fireTexture);


	float diameter = 2.0f * radius;

	fireSprite.setScale(diameter / FIRE_TEXTURE_SIZE, diameter / FIRE_TEXTURE_SIZE);
}



void FirePool::update(float dt) {
	if (dead) { return; }

	elapsed += dt;
	tickTimer += dt;

	if (!onGround) {

		// to move the fire pool on ground
		velocityY += 20.0f * dt; 

		 // for terminal velocity
		if (velocityY > 15.0f) velocityY = 15.0f;

		positionY += velocityY * dt * 60.0f; // to move it faster

		// Also a timer to make sure it does not remain in the air for very long
		if (elapsed > 1.5f && !onGround) {
			dead = true;
			isAlive = false;
			return;
		}
	}

	hitbox.updateCoordinates(positionX, positionY);

	if (elapsed >= duration) {

		dead = true;

		setIsAlive(false); return;
	}
}


void FirePool::render(sf::RenderWindow& window, Camera& cam) {

	if (dead) { return; }


	fireSprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
	window.draw(fireSprite);

}


void FirePool::applyDamageTo(Entity* e) {


	if (!e || dead || !e->getIsAlive()) { return; }


	//fool center in the world space
	// position x ands y are the top left x and y; to get the center x and y, we'll do, position + radius
	float poolCoordinateX = positionX + radius;
	float poolCoordinateY = positionY + radius;

	float entityCoordinateX = e->getPositionX() + (e->getHitbox().getWidth() * 0.5f);
	float entityCoordinateY = e->getPositionY() + (e->getHitbox().getHeight() * 0.5f);


	float dx = poolCoordinateX - entityCoordinateX;
	float dy = poolCoordinateY - entityCoordinateY;

	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance > radius) {
		return;
	}

	if (e->getIsMummy()) {
		e->takeDamage(999.0f);
		return;
	}


	if (tickTimer >= 0.1) {

		e->takeDamage(damagePerSec * 0.1f);

		tickTimer = 0; // 0 for the next tick to start accumulating
	}


}
