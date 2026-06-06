#include "BallisticProjectile.h"
#include"ExplosionBehavior.h"
#include "EntityManager.h"

static const float CELL_PIXEL = 32.0f;//will test  64 if this doesnt work

BallisticProjectile::BallisticProjectile(float x, float y, float vx, float vy, float damage,
	int t, float levelW, float levelH, char** lvl, int rows, int cols, int cellSize,
	float gravity, ExplosionBehavior* expl) :
	
	Projectile(x, y, 0.0f, damage, t, 10.0f, 10.0f,
		expl), vx(vx), vy(vy), gravity(gravity), levelWidthPx(levelW), levelHeightPx(levelH),
	lvl(lvl), lvlRows(rows), lvlCols(cols), cellSize(cellSize) { }

void BallisticProjectile::update(float dt) {
	if (!active) { return; }

	//vx is const
	vy += gravity * dt;
	positionX += vx * dt; positionY += vy * dt;

	getHitbox().updateCoordinates(positionX, positionY);

	//out of bound
	if (positionX < 0.0f || positionX > levelWidthPx || positionY < 0.0f || positionY > levelHeightPx) {
		deactivate();
		return;
	}


	//in order to avoid delay in explosion and to avoid grenade going inside the tile, doing tile collision here

	int tileRow = 0; int tileCol = 0;
	if (hitsSolidTile(tileRow, tileCol)) {

		//snapping the grenade to sit ontop of the tile
		positionY = (float)(tileRow * cellSize) - 10.0f;


		//syncing the hit box again
		getHitbox().updateCoordinates(positionX, positionY);


		onHit(nullptr);//will explode and deactivate;nullptr is for non entity tile



	}

	//collision detected by projectileManager
}

void BallisticProjectile::onHit(Entity* target) {

	if (!active) { return; }


	if (target != nullptr) {//meaning it was still in air and hit an enemy or player
		int type = target->getHitbox().getType();
		if (type == ColliderType::Player || type == ColliderType::Enemy || type == ColliderType::Vehicle) {
			DamagableEntity* d = (DamagableEntity*)target;
			d->takeDamage((int)damageInflicted);
		}
		

	}

	if (explosion != nullptr && entityManager != nullptr) {
		explosion->explode(positionX + 5.0f, positionY + 5.0f, *entityManager);
	}

	deactivate();
}
	
void BallisticProjectile::render(sf::RenderWindow& window, Camera& cam) {

	if (!active) { return; }

	sprite.setPosition(positionX - cam.getOffsetX(), positionY - cam.getOffsetY());
	window.draw(sprite);

}

bool BallisticProjectile::hitsSolidTile(int& outRow, int& outCol) const {

	if (!lvl) { return false; }

	//checking the collision of all thefourhitboxesof theprojectile

	float corners[4][2] = {
		positionX, positionY,
		positionX + 10.0f, positionY,
		positionX, positionY + 10.0f,
		positionX + 10.0f, positionY + 10.0f
	};

	for (int i = 0; i < 4; i++) {

		//converting those pixels to grid tiles index by index

		int col = (int)(corners[i][0] / cellSize);
		int row = (int)(corners[i][1] / cellSize);

		//skippingcorners outside  the grid boundary

		if (col < 0 || col >= lvlCols) {
			continue;
		}

		if (row < 0 || row >= lvlRows) {
			continue;
		}

		char tile = lvl[row][col];


		//checking solid tile
		if (tile != ' ' && tile != '~') {//if not air or water, collision willbe there
			outRow = row;
			outCol = col;
			return true;
		}
	}

	return false;
}

HandGrenade::HandGrenade(float x, float y, float vx, float vy, int t, float levelW, float levelH,
	 char** lvl, int rows, int cols, int cellSize) :


	BallisticProjectile(x, y, vx, vy, 5.0f, t, levelW, levelH, lvl, rows, cols, cellSize,
		600.0f, //gravity is 600
		new ExplosionBehavior(3.0f * CELL_PIXEL, 5.0f, false, 0.0f)) {

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Grenade.png");
	sprite.setTexture(texture);

	int frames[] = { 4 };
	float timers[] = { 0.1f };
	animator = new Animator(&sprite, 1, frames, timers, 32);
	
	animationRow[AnimationState::IDLE] = 0;
}


FireBombGrenade::FireBombGrenade(float x, float  y, float vx, float vy, int t, float levelW, float levelH, char** lvl, int rows, int  cols, int cellSize) :
	BallisticProjectile(x, y, vx, vy, 5.0f, t, levelW, levelH, lvl,rows, cols, cellSize, 600.0f,
		new ExplosionBehavior(3.0f * CELL_PIXEL, 5.0f, true, 10.0f)) {

	texture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/Bomb Explosive.png");
	sprite.setTexture(texture);
	
	int frames[] = { 4 };
	float timers[] = { 0.1f };
	animator = new Animator(&sprite, 1, frames, timers, 32);
	
	animationRow[AnimationState::IDLE] = 0;
	currentAnimRow = AnimationState::IDLE;
}