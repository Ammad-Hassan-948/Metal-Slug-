#include "ProjectileManager.h"
#include "EntityManager.h"
#include "Entity.h"

#include <iostream>


//weapon constants

static const float BULLET_SPEED = 800.0f;
static const float ROCKET_SPEED = 500.0f;
static const float ROCKET_DAMAGE = 5.0f;
static const float ROCKET_RADIUS = 96.0f; // 3 blocks




ProjectileManager::ProjectileManager():count(0), lvl(nullptr), lvlRows(0), lvlCols(0),
cellSize(32), levelWidthPx(0.0f), levelHeightPx(0.0f), entityManager(nullptr)
{

	for (int i = 0; i < MAX_PROJECTILES; i++) {
		projectiles[i] = nullptr;
	}
}

ProjectileManager::~ProjectileManager()
{

	for (int i = 0; i < MAX_PROJECTILES; i++) {
		delete projectiles[i];
		projectiles[i] = nullptr;
	}
	
}

void ProjectileManager::setLevel(char** level, int rows, int cols, int CellSize, EntityManager* manager)
{
	lvl = level;
	lvlRows = rows; lvlCols = cols; cellSize = CellSize;
	levelWidthPx = (float)(cols * cellSize);
	levelHeightPx = (float)(rows * cellSize);

	entityManager = manager;
}

void ProjectileManager::clear()
{
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		if (projectiles[i] != nullptr) {
			delete projectiles[i];
			projectiles[i] = nullptr;
		}
	}
	count = 0;
}

void ProjectileManager::update(float dt)
{
	for (int i = 0; i < MAX_PROJECTILES; i++) {

		if (projectiles[i] == nullptr || !projectiles[i]->isActive()) { continue; }

		projectiles[i]->update(dt);
	}
}

void ProjectileManager::checkTileCollision()
{
	if (!lvl) { return; }

	//laser beam and ballistic projectiles self detect their laser beams inside their own update functions

	for (int i = 0; i < MAX_PROJECTILES; i++) {

		if (projectiles[i] == nullptr) {
			continue;
		}

		if (!projectiles[i]->isActive()) { continue; }

		if (projectiles[i]->isLaser()) { continue; }

		if (projectiles[i]->isBallistic()) { continue; }


		float px = projectiles[i]->getPositionX();
		float py = projectiles[i]->getPositionY();


		float pw = projectiles[i]->getHitbox().getWidth();
		float ph = projectiles[i]->getHitbox().getHeight();


		int columnStart = (int)(px / cellSize); int columnEnd = (int)((px + pw) / cellSize);
		int rowStart = (int)(py / cellSize); int rowEnd = (int)((py + ph) / cellSize);

		if (columnStart < 0) { columnStart = 0; }
		if (columnEnd >= lvlCols) {
			columnEnd = lvlCols - 1;
		}

		if (rowStart < 0) {
			rowStart = 0;
		}
		if (rowEnd >= lvlRows) {
			rowEnd = lvlRows - 1;
		}


		bool hit = false;

		for (int row = rowStart; row <= rowEnd && !hit; row++) {
			for (int col = columnStart; col <= columnEnd && !hit; col++) {

				if (!isSolid(row, col)) {
					continue;
				}

				float tempX = (float)(col * cellSize);
				float tempY = (float)(row * cellSize);

				Collider tileBox(tempX, tempY, (float)cellSize, (float)cellSize, 0.0f, 0.0f, ColliderType::World);


				if (projectiles[i]->getHitbox().checkCollision(tileBox)) {
					projectiles[i]->onHit(nullptr);
					hit = true;
				}

			}


			
		}
	}
}

void ProjectileManager::checkEntityCollision(EntityManager& manager)
{

	int entityCount = manager.getCount();

	for (int i = 0; i < MAX_PROJECTILES; i++) {


		if (projectiles[i] == nullptr) {
			continue;
		}

		if (!projectiles[i]->isActive()) { continue; }

		bool isLaser = projectiles[i]->isLaser();

		for (int j = 0; j < entityCount; j++) {
			Entity* e = manager.getEntity(j);

			if (!e || !e->getIsAlive()) { continue; }

			int targetType = e->getHitbox().getType();
			bool isBulletPlayerOwned = projectiles[i]->getIsPlayerOwned();

			// Player bullets only hit enemies
			if (isBulletPlayerOwned && targetType != ColliderType::Enemy) { continue; }

			// Enemy bullets only hit players (and player vehicles)
			if (!isBulletPlayerOwned && targetType != ColliderType::Player && targetType != ColliderType::Vehicle) { continue; }

			//no aabb for laser

			if (isLaser) {
				LaserBeam* laser = (LaserBeam*)projectiles[i];

				if (laser->passesThrough(e->getPositionX(), e->getPositionY(),
					e->getHitbox().getWidth(), e->getHitbox().getHeight())) {

					laser->onHit(e);

				}
				else {
					continue;
				}
			}

			if (projectiles[i]->getHitbox().checkCollision(e->getHitbox())) {

				projectiles[i]->onHit(e);//projectile deactivated on hit

				break;
			}

		}
	}
}

void ProjectileManager::removeDeadProjectiles() {

	for (int i = 0; i < MAX_PROJECTILES; i++) {

		if (projectiles[i] == nullptr) { continue; }

		if (!projectiles[i]->isActive()) {

			delete projectiles[i];

			projectiles[i] = nullptr;

			count--;
		}
	}
}


void ProjectileManager::render(sf::RenderWindow& window, Camera& cam) {

	for (int i = 0; i < MAX_PROJECTILES; i++) {

		if (projectiles[i] == nullptr) {
			continue;
		}

		if (!projectiles[i]->isActive()) {
			continue;
		}

		projectiles[i]->render(window, cam);
	}
}

void ProjectileManager::spawnBullet(float x, float y, float angleDeg, float damage, float speed, int t)
{
	StraightProjectile* p = new StraightProjectile(x, y, angleDeg, damage, speed, t, levelWidthPx, levelHeightPx);

	p->setEntityManager(entityManager);

	addProjectile(p);
}

void ProjectileManager::spawnRocket(float x, float y, float angleDeg, int t)
{
	ExplosionBehavior* expl = new ExplosionBehavior(ROCKET_RADIUS, ROCKET_DAMAGE, false, 0.0f);

	StraightProjectile* p = new StraightProjectile(x, y, angleDeg, ROCKET_DAMAGE, ROCKET_SPEED, t,
		levelWidthPx, levelHeightPx, 0.0f, expl);

	p->setEntityManager(entityManager);

	addProjectile(p);
}

void ProjectileManager::spawnLaser(float x, float y, float angleDeg, int t)
{

	LaserBeam* p = new LaserBeam(x, y, angleDeg, t, levelWidthPx, levelHeightPx);
	p->setEntityManager(entityManager);
	addProjectile(p);

}

void ProjectileManager::spawnFlame(float x, float y, float angleDeg, int t)
{
	FlameShot* p = new FlameShot(x, y, angleDeg, t, levelWidthPx, levelHeightPx, (float)cellSize);
	p->setEntityManager(entityManager);
	addProjectile(p);
}

void ProjectileManager::spawnHandGrenade(float x, float y, float vx, float vy, int t)
{
	HandGrenade* p = new HandGrenade(x, y, vx, vy, t, levelWidthPx, levelHeightPx, lvl, lvlRows, lvlCols, cellSize);
	p->setEntityManager(entityManager);
	addProjectile(p);
}

void ProjectileManager::spawnFireBombGrenade(float x, float y, float vx, float vy, int t)
{
	FireBombGrenade* p = new FireBombGrenade(x, y, vx, vy, t, levelWidthPx, levelHeightPx, lvl, lvlRows, lvlCols, cellSize);
	p->setEntityManager(entityManager);
	addProjectile(p);
}

Projectile* ProjectileManager::getProjectile(int i) const
{
	return projectiles[i];
}

char ProjectileManager::getTileDesignAt(float x, float y) const
{
	if (lvl == nullptr) return ' ';

	int col = (int)(x / cellSize);
	int row = (int)(y / cellSize);

	if (row < 0 || row >= lvlRows || col < 0 || col >= lvlCols)
		return ' ';
	
	return lvl[row][col];
}


void ProjectileManager::spawnExplosion(float x, float y, float scale)
{
	if (entityManager) {
		ExplosionBehavior expl(96.0f * scale, 10.0f * scale, true, 3.0f);
		expl.explode(x, y, *entityManager);
	}

	// visual burst of 8 bullets

	float angles[] = { 0, 45, 90, 135, 180, 225, 270, 315 };
	for (int i = 0; i < 8; i++) {
		spawnBullet(x, y, angles[i], 2.0f * scale, 600.0f, 0);
	}
}

bool ProjectileManager::addProjectile(Projectile* p)
{
	if (!p) {
		return false;
	}

	if (count >= MAX_PROJECTILES) {

		std::cout << "Max Projectiles reached cant add more " << endl;
		delete p; 
		return false;
	}

	for (int i = 0; i < MAX_PROJECTILES; i++) {

		if (projectiles[i] == nullptr) {

			projectiles[i] = p;
			count++;
			return true;
		}
	}

	delete p; return false;
}

bool ProjectileManager::isSolid(int row, int col) const
{

	if (!lvl) {
		return false;
	}

	if (row < 0 || row >= lvlRows) {
		return false;
	}

	if (col < 0 || col >= lvlCols) {
		return false;
	}

	char t = lvl[row][col];

	return (t != ' ' && t != '~'); //not air or water

	
}





