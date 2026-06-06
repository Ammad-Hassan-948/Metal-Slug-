#include "Projectile.h"
#include "ExplosionBehavior.h"
#include "Camera.h"


Projectile::Projectile(float x, float y,
	float angle, float damage, int t, float w, float h,
	ExplosionBehavior* expl) :Entity(x, y, 0.0f, 0.0f, 0.0f, w, h, 0.0f, 0.0f, t), damageInflicted(damage), angle(angle),
	active(true), explosion(expl),
	entityManager(nullptr)
{
	positionX = x;
	positionY = y;

	isPlayerOwned = (t == ColliderType::PlayerBullet);;
}

Projectile::~Projectile() {
	delete explosion; //deleting the explosion component as it was composition
	explosion = nullptr;

}



void Projectile::render(sf::RenderWindow& window, Camera& cam) {
	if (!active) { return; }

	float screenX = positionX - cam.getOffsetX();
	float screenY = positionY - cam.getOffsetY();

	sprite.setPosition(screenX, screenY);
	window.draw(sprite);
}

bool Projectile::isActive() const {
	return active;
}
bool Projectile::isDead() const {
	return !active;
}


