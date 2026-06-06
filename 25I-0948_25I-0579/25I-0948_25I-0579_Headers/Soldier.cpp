#include "TransformationState.h"
#include "Soldier.h"
#include"Weapon.h"
#include "ProjectileManager.h"

Soldier::Soldier(float startX, float startY, float velocityX, float velocityY, float gravity, float width, float height, float offsetX, float offsetY, int colliderType, int hp, const char* name) ://AMMAD - added const to the name
	DamagableEntity(startX, startY, velocityX, velocityY, gravity, width, height, offsetX, offsetY, colliderType, hp, name) {

	// also initialie the base stats
	this->lives = 2;
	this->grenades = 10;
	this->direction = 1;
	this->baseSpeed = 5.0f;
	saturation = 0;
	fireRate = 1.0f;
	this->pistol = nullptr;
	this->melee = nullptr;
	this->currentState = nullptr;
	this->currentWeapon = nullptr;
	this->specialWeapon = nullptr;
	this->projMgr = nullptr;
	isImmune = false;
	fireRateTimer = 0.0f;
	
}

Soldier::~Soldier()
{
	if (currentState != nullptr) {
		delete currentState;
		currentState = nullptr;
	}

	if (currentWeapon != nullptr) {
		delete currentWeapon;
		currentWeapon = nullptr;
	}

	// pistol and melee are not yet allocated; skipping delete to avoid UB
}

void Soldier::changeState(TransformationState* newState)
{
	if (currentState != nullptr) {
		// to trigger exit function of current state
		currentState->exit(this);
		delete currentState;
	}

	currentState = newState;
	// now to get back into other state
	currentState->enter(this);
}

void Soldier::equipWeapon(Weapon* newWeapon)
{
	if (specialWeapon != nullptr)
		delete specialWeapon;

	specialWeapon = newWeapon;

	if (specialWeapon != nullptr)
		currentWeapon = specialWeapon;

	// also set manager for new weapon if we have one
	if (specialWeapon != nullptr && projMgr != nullptr) {
		specialWeapon->setProjectileManager(projMgr);
	}
}

void Soldier::setProjectileManager(ProjectileManager* pm)
{
	this->projMgr = pm;
	if (pistol != nullptr)
		pistol->setProjectileManager(pm);
	if (specialWeapon != nullptr)
		specialWeapon->setProjectileManager(pm);
	if (melee != nullptr)
		melee->setProjectileManager(pm);
}

float Soldier::getFireRateTimer() const
{
	return fireRateTimer;
}

void Soldier::setFireRateTimer(float t)
{
	fireRateTimer = t;
}

void Soldier::update(float passedTime)
{
	// here i would first call the gravity to keep things going
	applyGravity();

	if (fireRateTimer > 0)
		fireRateTimer -= passedTime;

	// now i will update the player states
	currentState->update(this, passedTime);

	// also update the new coordinates in the hitbox
	hitbox.updateCoordinates(positionX, positionY);

	
	if (specialWeapon != nullptr && specialWeapon->weaponEmpty()) {
		delete specialWeapon;
		specialWeapon = nullptr;
		currentWeapon = pistol;
	}

	

	if (animator != nullptr) {
		// if direction is -1 flip the direction of sprite so it can show to left
		if (direction == -1)
			animator->setFlipDir(true);
		// else flip to show it to right
		else
			animator->setFlipDir(false);

		animator->update(passedTime);
	}
}

void Soldier::render(RenderWindow& window, Camera& cam)
{
	sprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
	window.draw(sprite);
}

float Soldier::getBaseSpeed() const
{
	return baseSpeed;
}

Weapon* Soldier::getCurrentWeapon() const
{
	return currentWeapon;
}

Weapon* Soldier::getSpecialWeapon() const
{
	return specialWeapon;
}

Weapon* Soldier::getPistol() const
{
	return pistol;
}

Weapon* Soldier::getMelee() const
{
	return melee;
}

float Soldier::getfireRate() const
{
	return fireRate;
}

int Soldier::getLives() const
{
	return lives;
}

void Soldier::setLives(int l)
{
	lives = l;
}

void Soldier::setPistol(Weapon* p)
{
	if (pistol != nullptr)
		delete pistol;
	pistol = p;
	if (currentWeapon == nullptr)
		currentWeapon = pistol;
}

int Soldier::getGrenades()
{
	return grenades;
}

void Soldier::setCurrentWeapon(Weapon* changed)
{
	currentWeapon = changed;
}

ProjectileManager* Soldier::getProjectileManager() const
{
	return projMgr;
}

void Soldier::handleMouse(Vector2f worldPosition)
{
	if (currentState != nullptr) {
		currentState->handleMouse(this, worldPosition);

	}
	
}

void Soldier::setFireRate(float f)
{
	fireRate = f;
}

void Soldier::addGrenades(int g)
{
	grenades += g;
}

void Soldier::setGrenades(int s)
{
	grenades = s;
}

void Soldier::addSaturation(int s)
{
	saturation += s;
}

