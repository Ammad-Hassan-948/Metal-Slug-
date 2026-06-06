#pragma once

#include "Projectile.h"
#include "ExplosionBehavior.h"

class StraightProjectile :public Projectile {
	protected:
		float speed;//pixels per second
		float maxRange; // will set to 0 as unlimited for a bullet and 5 blocks as for flame shot
		float distanceTravelled;
		float vx; float vy; //computed once and will not change in straight projectile

		float levelWidthPx;
		float levelHeightPx;


		sf::Sprite beamSprite; sf::Texture beamTexture;
		sf::Sprite laserSprite; sf::Texture laserTexture;

public:
	StraightProjectile(float x, float y, float angle, float damage, float speed, int t, 
		float levelW, float levelH, float maxRange = 0.0f, ExplosionBehavior* explosion = nullptr);

	void update(float dt) override;

	void onHit(Entity* target) override;

	void render(sf::RenderWindow& window, Camera& cam) override;


protected:
	
	//protected so subclasses can call it to recompute
	void computeVelocity();
};


class LaserBeam : public StraightProjectile {
private:
	bool firedThisFrame; 

	float endX;//where the world will end
	float beamY;//world y center of the beam at position Y + 2


	sf::Texture beamTexture;
	sf::Sprite beamSprite;

public:
	
	LaserBeam(float x, float y, float angle, int t, float levelW, float levelH);

	void update(float dt);

	void onHit(Entity* target);

	void render(sf::RenderWindow& window, Camera& cam) override;


	bool passesThrough(float ex, float ey, float ew, float eh) const;

	float getEndX() const { return endX; }

	float getBeamY() const { return beamY; }

	bool isLaser() const override { return true; }
};



class FlameShot : public StraightProjectile {

private:
	float damagePerSec;
	float tickTimer;//accumulates dt and when its >= 0.1, one damage tick is applied

public:

	FlameShot(float x, float y, float angle, int t, float levelW, float levelH, float cellSize);

	void update(float dt) override;

	void onHit(Entity* target) override;
};




