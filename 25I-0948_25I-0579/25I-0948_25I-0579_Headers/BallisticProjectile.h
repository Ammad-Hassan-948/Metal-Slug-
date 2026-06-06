#pragma once
#include "Projectile.h"

class BallisticProjectile :public Projectile {
	//vx stays constant
	//vy increases every frameas gravity is added to it
	
protected:
	float vx;
	float vy;//at peak vy =0
	float gravity;//higher value, willland sooner
	float levelWidthPx;
	float levelHeightPx;

	char** lvl; int lvlRows; int lvlCols;
	int cellSize;//same pixel per tile used previosuly


public:

	BallisticProjectile(float  x, float y, float vx, float  vy, float damage, int t, float levelW, float  levelH,
		char** lvl, int rows, int cols, int cellSize, float gravity = 600.f, ExplosionBehavior* expl = nullptr);
	
	void update(float dt)override;
	void onHit(Entity* target)override;
	void render(sf::RenderWindow& window, Camera& cam)override;  

	bool isBallistic() const override { return true; }


private:

	bool hitsSolidTile(int& outRow, int& outCol)const;
};



class HandGrenade :public BallisticProjectile {
public:
	HandGrenade(float x, float y, float vx, float vy, int t, float levelW,
		float levelH, char** lvl, int rows, int cols, int cellSize);
};

class FireBombGrenade :public BallisticProjectile {
public:
	FireBombGrenade(float x, float y, float vx, float vy, int t, float levelW, float levelH,
		char** lvl, int rows, int cols, int cellSize);
};