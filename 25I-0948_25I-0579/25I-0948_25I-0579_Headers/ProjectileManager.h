#pragma once
#include "Straight Projectile.h"
#include "BallisticProjectile.h"

class EntityManager;
class Camera;

class ProjectileManager {

private:
	static const int MAX_PROJECTILES = 256;

	Projectile* projectiles[MAX_PROJECTILES];

	int count; //no of occupied

	char** lvl;
	int lvlRows; int lvlCols; int cellSize; 
	int levelWidthPx; int levelHeightPx; //level height and width pixels

	EntityManager* entityManager;

	bool addProjectile(Projectile* p);

	bool isSolid(int row, int col) const;


public:
	ProjectileManager();
	~ProjectileManager();


	void setLevel(char** lvl, int rows, int cols, int cellSize, EntityManager* manager);
	void clear();
	void update(float dt);
	void checkTileCollision();
	void checkEntityCollision(EntityManager& manager);

	void removeDeadProjectiles();
	void render(sf::RenderWindow& window, Camera& cam);

	//spawners

	void spawnBullet(float x, float y, float angleDeg, float damage, float speed, int t);
	void spawnRocket(float x, float y, float angleDeg, int t);
	void spawnLaser(float x, float y, float angleDeg, int t);
	void spawnFlame(float x, float y, float angleDeg, int t);

	void spawnHandGrenade(float x, float y, float vx, float vy, int t);

	void spawnFireBombGrenade(float x, float y, float vx, float vy, int t);

	void spawnExplosion(float x, float y, float scale);

	Projectile* getProjectile(int i)const;

	int getMaxProjectiles() const {
		return MAX_PROJECTILES;
	}

	int getCount() const {
		return count;
	}


	// to get the tile to check for biomes
	char getTileDesignAt(float x, float y) const; 


};

