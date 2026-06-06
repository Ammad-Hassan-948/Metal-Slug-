#include "Entity.h"
#include"PlayerSoldier.h"

Entity::Entity(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType) :
	positionX(startX), positionY(startY), velocityX(velocityX), velocityY(velocityY), gravity(gravity), isAlive(true),
	onGround(false), visible(true), isDying(false), playerEntity(false), isMummy(false), hitbox(startX, startY, width, height, offsetX, offsetY, colliderType) {

	this->manager = nullptr;
	// i will initialize animator later when i have the specific sprite
	animator = nullptr;
	this->baseSpeed = 5.0f;

	// put current animation state to idle
	currentAnimRow = AnimationState::IDLE;

	// loop through the whole array to set it to -1 so special objects can set it to their specific state and -1 can act as a flag
	for (int i = 0; i < AnimationState::TOTAL_STATES; i++)
		animationRow[i] = -1;
}

Entity::~Entity()
{
	delete animator;
}

Collider& Entity::getHitbox()
{
	return hitbox;
}

bool Entity::getIsAlive() const
{
	return isAlive;
}

float Entity::getPositionX() const
{
	return positionX;
}

float Entity::getPositionY() const
{
	return positionY;
}

float Entity::getVelocityX() const
{
	return velocityX;
}

float Entity::getVelocityY() const
{
	return velocityY;
}

bool Entity::getOnGround() const
{
	return onGround;
}

bool Entity::getVisible() const
{
	return visible;
}

Animator* Entity::getAnimator()
{
	return animator;
}

float Entity::getBaseSpeed() const
{
	return baseSpeed;
}

void Entity::setOnGround(bool g)
{
	onGround = g;
}

void Entity::setIsAlive(bool a)
{
	isAlive = a;
}

void Entity::setVisible(bool v)
{
	visible = v;
}

void Entity::setPositionX(float pos)
{
	positionX = pos;
}

void Entity::setPositionY(float pos)
{
	positionY = pos;
}

void Entity::setVelocityX(float vel)
{
	velocityX = vel;
}

void Entity::setVelocityY(float vel)
{
	velocityY = vel;
}

void Entity::setEntityManager(EntityManager* e)
{
	manager = e;
}

void Entity::applyGravity()
{
	if (!onGround) {
		velocityY += gravity;

		// for perfect terminal velocity i will set a threshhold of max velocity to be 15 to get to terminal velocity 
		if (velocityY > 15)
			velocityY = 15;
	}
}

void Entity::setTexture(const Texture& tex) {
	sprite.setTexture(tex);
}

void Entity::setScale(float scaleX, float scaleY) {
	sprite.setScale(scaleX, scaleY);
}


void Entity::doAnimation(int state)
{
	// first get the no of row which we have to play from our array
	int animRow = animationRow[state];

	// check if row is not our flag -1 or animator is not initialized
	if (animRow != -1 && animator != nullptr) {
		// check if we are already not on this state
		if (currentAnimRow != state) {
			// change state by calling function
			animator->setState(animRow);
			currentAnimRow = state;
		}
	}
}

bool Entity::isPlayer()
{
	return playerEntity;
}

bool Entity::getIsMummy()
{
	return isMummy;
}



