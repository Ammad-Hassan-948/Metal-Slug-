#include "DamagableEntity.h"

DamagableEntity::DamagableEntity(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name) :
	Entity(startX, startY, velocityX, velocityY, gravity, width, height, offsetX, offsetY, colliderType), hp(hp) {

	aimAngle = 0.0f;
	fireRate = 1.0f;
	// copy the name dynamically using my helper
	this->name = copyString(name);
	// set default value for direction
	direction = 1;
}

DamagableEntity::~DamagableEntity()
{
	delete[] name;
}

int DamagableEntity::getHp() const
{
	return hp;
}

int DamagableEntity::getDirection() const
{
	return direction;
}

float DamagableEntity::getAimAngle() const
{
	return aimAngle;
}

float DamagableEntity::getFireRate() const
{
	return fireRate;
}

void DamagableEntity::setDirection(int dir)
{
	direction = dir;
}

void DamagableEntity::setAimAngle(float a)
{
	aimAngle = a;
}

void DamagableEntity::setFireRate(float f)
{
	fireRate = f;
}

void DamagableEntity::render(RenderWindow& window, Camera& cam)
{
	sprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
	window.draw(sprite);
}
