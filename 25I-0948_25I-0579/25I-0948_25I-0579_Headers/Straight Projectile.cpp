#include "Straight Projectile.h"
#include "ExplosionBehavior.h"
#include "EntityManager.h"
#include "DamagableEntity.h"

#include <cmath>


static const float PI = 3.14159265f;
static const float BEAM_TEX_SIZE = 1.0f;



StraightProjectile::StraightProjectile(float x, float y, float angle, float damage, float speed, int t, float levelW, float levelH, float maxRange, ExplosionBehavior* explosion) :
	Projectile(x, y, angle, damage, t, 8.0f, 8.0f, explosion), speed(speed), maxRange(maxRange),//bullet hit box is 8x8 pixels

	distanceTravelled(0.0f), vx(0.0f), vy(0.0f), levelWidthPx(levelW), levelHeightPx(levelH)
{

	if (explosion == nullptr) {
		texture.loadFromFile("assets/Sprites/Enemies/Bullet.png");
		sprite.setTexture(texture);
		
		int frames[] = { 1 };
		float timers[] = { 0.1f };
		animator = new Animator(&sprite, 1, frames, timers, 16); // Bullet is small
	}
	else {
		texture.loadFromFile("assets/Sprites/Enemies/Rocket Projectile.png");
		sprite.setTexture(texture);

		int frames[] = { 3 }; 
		float timers[] = { 0.05f };
		animator = new Animator(&sprite, 1, frames, timers, 64);
	}
	
	animationRow[AnimationState::IDLE] = 0;
	currentAnimRow = AnimationState::IDLE;


	computeVelocity();
}

void StraightProjectile::computeVelocity() {

	float rad = angle * PI / 180.0f;
	vx = speed * std::cos(rad); //cos0 for full horizontal speed,90 for no horizontal movement and 180  for full leftward
	vy = -speed * std::sin(rad);//sin 90 taken as -1 due to SFML, sin 0 for no vertical movement; downward at 270
}

void StraightProjectile::update(float dt) {

	//here my update is only handling movement right now; tile and entity collision checked in projectileManager

	if (!active) { return; }

	//moving the projectile entity's x and y positions

	positionX += vx * dt;
	positionY += vy * dt;
	distanceTravelled += speed * dt;//dostance the projectile has travelled

	//syncing the collider headbox to the new world position
	getHitbox().updateCoordinates(positionX, positionY);

	
	if (positionX < 0.0f || positionX > levelWidthPx || positionY < 0.0f || positionY > levelHeightPx) {//deactivating ou tof bound projectile
		deactivate();
		return;
	}


	if (maxRange > 0.0f && distanceTravelled >= maxRange){
		deactivate();
		return;

	}

	if (animator) animator->update(dt);



}


void StraightProjectile::onHit(Entity* target) {
	if (!active) { return; 
	}
	if (target != nullptr) {//meaning it was still in air and hit an enemy or player

		int type = target->getHitbox().getType();

		if (type == ColliderType::Player || type == ColliderType::Enemy || type == ColliderType::Vehicle) {
			DamagableEntity* d = (DamagableEntity*)target;
			d->takeDamage((int)damageInflicted);
		}


	}
	

	if (explosion != nullptr && entityManager != nullptr) {
		explosion->explode(positionX, positionY, *entityManager);
	}


	deactivate();
}


void StraightProjectile::render(sf::RenderWindow& window, Camera& cam) {
	if (!active) { return; }


	sprite.setPosition(positionX - cam.getOffsetX(),
		positionY - cam.getOffsetY());
	//if the object is at 600px in the worldandthe camera has scrolled 500px, then its on 100 pixel on screen

	window.draw(sprite);
}

LaserBeam::LaserBeam(float x, float y,
	float angle, int t, float levelW, float levelH) :
	StraightProjectile(x, y, angle, 9999.0f, 0.0f, t, levelW, levelH, 0.0f, nullptr),//speed 0 because beam doesnt move

	firedThisFrame(false), endX(x), beamY(y) {

	getHitbox().resizeCollider(x, y, levelW, 4.0f, 0.0f, 0.0f, t);//making the hitbox of laser beam a thinn horizontal line
	//the collider spans the entire level beam in width and 4px in height

	beamTexture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Laser.png");
	beamSprite.setTexture(beamTexture);
	beamSprite.setScale(1.0f, 1.0f);
	
	int frames[] = { 1 };
	float timers[] = { 0.1f };
	animator = new Animator(&sprite, 1, frames, timers, 32);
}


void LaserBeam::update(float dt) {
	if (!active) {
		return;
	}

	if (!firedThisFrame) {
		firedThisFrame = true;
		beamY = positionY + 2.0f;//beam y is the vertical centre of the 4pixel tall hitbox

		endX = (vx >= 0.0f) ? levelWidthPx : 0.0f;
		//vx > 0 means firing right, beam ends at right edge of level
		// vx < 0 means firing left, beam ends at left edge so endX = 0
		//resizingthe hitbox tospawnex
		float beamLeft = (vx >= 0.0f) ? positionX : endX;

		float beamWidth = (vx >= 0.0f) ? (endX - positionX) : (positionX - endX);

		getHitbox().resizeCollider(beamLeft, positionY, beamWidth, 4.0f, 0.0f, 0.0f,
			getHitbox().getType());

		beamSprite.setScale(beamWidth / BEAM_TEX_SIZE, 4.0f / BEAM_TEX_SIZE);

	}

	else {
		//collision and rendering had already happened last frame
		deactivate();
	}
}


void LaserBeam::onHit(Entity* target) {
	if (target != nullptr) {
		int type = target->getHitbox().getType();

		if (type == ColliderType::Player || type == ColliderType::Enemy || type == ColliderType::Vehicle) {
			DamagableEntity* d = (DamagableEntity*)target;
			d->takeDamage(999.0f); //instantly killing; need to fix the parameter of hthe function
		}
	}
}

void LaserBeam::render(sf::RenderWindow& window, Camera& cam) {
	if (!active|| !firedThisFrame) {
		return;
	}

	float beamLeft = (vx >= 0.0f) ? positionX : endX;

	beamSprite.setPosition(beamLeft - cam.getOffsetX(), positionY - cam.getOffsetY());

	window.draw(beamSprite);


}

bool LaserBeam::passesThrough(float ex, float ey, float ew, float eh) const {

	if (!active || !firedThisFrame) {
		return false;
	}

	bool yHit = (beamY >= ey) && (beamY <= ey + eh);

	if (!yHit) {
		return false;
	}

	float beamLeft = (vx >= 0.0f) ? positionX : endX;
	float beamRight = (vx >= 0.0f) ? endX : positionX;

	return (beamRight >= ex) && (beamLeft <= ex + ew);

}


FlameShot::FlameShot(float x, float y,
	float angle, int t, float levelW, float levelH, float cellSize) :
	StraightProjectile(x, y, angle, 2.0f, 400.0f, t, levelW, levelH, 12.0 * cellSize, nullptr),
	damagePerSec(2.2f), tickTimer(0.0f) {

	getHitbox().resizeCollider(x, y, 12.0, 10.0f, 0.0f, 0.0f, t);

	texture.loadFromFile("assets/Sprites/Enemies/Fire Bomb Explosive.png");
	sprite.setTexture(texture);
	
	int frames[] = { 5 };
	float timers[] = { 0.1f };
	animator = new Animator(&sprite, 1, frames, timers, 32);
	
	animationRow[AnimationState::IDLE] = 0;
	


}

void FlameShot::update(float dt) {

	if (!active) { return; }

	tickTimer += dt;

	StraightProjectile::update(dt);//to get straight motion, bounds checking, and range limit
}

void FlameShot::onHit(Entity* target) {
	if (!active) {
		return;
	}

	if (target == nullptr) {//has hit a tile
		deactivate(); return;
	}

	if (tickTimer >= 0.1f) {
		int type = target->getHitbox().getType();

		if (type == ColliderType::Player || type == ColliderType::Enemy || type == ColliderType::Vehicle) {
			DamagableEntity* d = (DamagableEntity*)target;

			// calculate floating point damage
			float damage = damagePerSec * 0.1f;

			// if damage is greater than 0 atleast one damage should be dealt than
			int finalDamage = (damage > 0 && damage < 1.0f) ? 1 : (int)damage;
			d->takeDamage(finalDamage);
			tickTimer = 0.0f;
		}
	}

	if (target->getIsMummy()) {
		int type = target->getHitbox().getType();

		if (type == ColliderType::Player || type == ColliderType::Enemy || type == ColliderType::Vehicle) {
			DamagableEntity* d = (DamagableEntity*)target;
			d->takeDamage(999);
		}
	}
}










