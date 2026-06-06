#pragma once
#include "Entity.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>

//firepool is the hazard zone created by the fireBombGrenade explosion or Iron Nokana boss flamethrower

//it stays in the world for a duration and damages entities

class FirePool :public Entity {

private:
	float radius;
	float damagePerSec;

	float duration;
	float elapsed;
	float tickTimer;//damage tick accumulator and each firePool projectile has its own tickTimer
	bool dead;

	sf::Texture fireTexture;
	sf::Sprite fireSprite;


public:
	//cx and cy are world center coordinates
	//entity stores top left
	// so position is world center coordinates - radius


	FirePool(float cx, float cy, float radius = 96.0f, float damagePerSec = 2.0f, float duration = 10.0f);

	void update(float dt);

	void render(sf::RenderWindow& window, Camera& cam) override;


	void applyDamageTo(Entity* entity);


	float getCentreX() const;
	float getCentreY() const;
	float getRadius() const;
};
