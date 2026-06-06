#pragma once
#include "SurvivalState.h"
#include "GameStateManager.h"
#include "ModeSelectState.h"
#include "MarcoRossi.h"
#include "EriKasamoto.h"
#include "FiolinaGermi.h"
#include "Tarma.h"
#include "MetalSlug.h"
#include "Vehicle.h"
#include "MenuState.h"
#include"Enemy.h"
#include"RebelSoldier.h"
#include "HairBusterRiberts.h"
#include "ProjectileManager.h"
#include "EntityManager.h"
#include "IronNokana.h"
#include "SeaSatan.h"
#include "UltimateBoss.h"
#include "SlugMariner.h"
#include"ProjectileManager.h"
#include"FirePool.h"
#include"Collectibles.h"
#include"HeavyMachineGun.h"
#include"LaserGun.h"
#include"LaserGun.h"
#include"FlameShotGun.h"
#include"ScoreManager.h"

#include <fstream>

#include<iostream>

using namespace std;


using namespace sf;

#include "Pistol.h"

SurvivalState::SurvivalState(GameStateManager* mgr, sf::RenderWindow* win, int startLevel) :manager(mgr), window(win), camera(1600, 900, LVL_WIDTH
	*CELL_SIZE, LVL_HEIGHT*CELL_SIZE){
	
	currentLevel = startLevel;
	lvl = NULL;
	currentCharacterIndex = 0;
	zPressed = false;

	bgTexture.loadFromFile("assets/Backgrounds/Background.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(
		(float)window->getSize().x / bgTexture.getSize().x,
		(float)window->getSize().y / bgTexture.getSize().y
	);

	bossTexture.loadFromFile("assets/Backgrounds/Boss-level.png");
	bossSprite.setTexture(bossTexture);
	bossSprite.setScale(
		(float)window->getSize().x / bossTexture.getSize().x,
		(float)window->getSize().y / bossTexture.getSize().y
	);
	




	//audioMgr.loadAndPlayMusic("assets/Metal Slug Water Sound.wav", "assets/main_theme_muffled.wav");
	









	wallTexture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/grass_block_side.png");
	wallSprite.setTexture(wallTexture);

	stoneTexture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/stone.png");
	stoneSprite.setTexture(stoneTexture);

	waterTexture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/water.jpeg");//adding andesite in place of water 
	waterSprite.setTexture(waterTexture);

	bedrockTexture.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/deepslate_top.png");
	bedrockSprite.setTexture(bedrockTexture);

		////lvl[11][5] = 'g';
		////lvl[11][6] = 'g';
		//lvl[11][7] = 'g';
		//lvl[11][8] = 'g';
		//lvl[11][9] = 'g';
		//lvl[11][10] = 'g';
		//lvl[11][11] = 'g';

	float spawnX = levelMgr.getSpawnCol() * CELL_SIZE;
	float spawnY = levelMgr.getSpawnRow() * CELL_SIZE;

	allPlayers[0] = new MarcoRossi(spawnX, spawnY);
	allPlayers[1] = new EriKasamoto(spawnX, spawnY);
	allPlayers[2] = new FiolinaGermi(spawnX, spawnY);
	allPlayers[3] = new Tarma(spawnX, spawnY);

	for (int i = 0; i < 4; i++) {
		allPlayers[i]->setPistol(new Pistol(-1));
		allPlayers[i]->setProjectileManager(&projMgr);
	}


	player = allPlayers[0];


	loadLevel(currentLevel);
	//if (currentLevel == 1) { loadLevelFromFile("assets/levels/level1.txt");}

	

	


	//entityMgr.add(player);

	redHueTexture.loadFromFile("assets/Sprites/blocks/red hue.png"); // This is going to be used for the red hue
	redHueSprite.setTexture(redHueTexture);
	redHueSprite.setScale(1, 1); 

	redHueSprite.setColor(sf::Color(255, 0, 0, 80));

	redHueSprite.setScale((float)window->getSize().x / redHueTexture.getSize().x, (float)window->getSize().y / redHueTexture.getSize().y);


	currentBoss = nullptr;
	bossPhase = 1;
}

ProjectileManager* SurvivalState::getProjectileManager()
{
	return &projMgr;
}



void SurvivalState::allocateLevel() {
	std::cout << "allocateLevel called" << std::endl;
	lvl = new char* [LVL_HEIGHT];

	for (int i = 0; i < LVL_HEIGHT; i++) {
		lvl[i] = new char[LVL_WIDTH];

		for (int j = 0; j < LVL_WIDTH; j++) {
			lvl[i][j] = ' ';
		}
	}

	std::cout << "allocateLevel done" << std::endl;
}

void SurvivalState::freeLevel() {
	if (lvl == NULL) {
		return;
	}
	
		for (int i = 0; i < LVL_HEIGHT; i++) {
			delete[] lvl[i];
		}
		delete[] lvl;
		lvl = NULL;
	
}

void SurvivalState::loadLevel(int levelNum) {
	freeLevel();
	allocateLevel();

	currentBoss = nullptr;
	bossPhase = 1;

	// Clear leftover data from previous levels
	entityMgr.clear();
	projMgr.clear();
	projectileManager.clear();



	levelMgr.generateLevel(levelNum, lvl, player, &entityMgr, &projMgr);

	float sx = levelMgr.getSpawnCol() * CELL_SIZE;
	float sy = levelMgr.getSpawnRow() * CELL_SIZE;

	for (int i = 0; i < 4; i++) {
		allPlayers[i]->setPositionX(sx);
		allPlayers[i]->setPositionY(sy);
		allPlayers[i]->setVelocityX(0);
		allPlayers[i]->setVelocityY(0);
	}


	projMgr.setLevel(lvl, LVL_HEIGHT, LVL_WIDTH, CELL_SIZE, &entityMgr);

	projectileManager.setLevel(lvl, LVL_HEIGHT, LVL_WIDTH, CELL_SIZE, &entityMgr);
}





void SurvivalState::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		manager->changeState(new ModeSelectState(manager, window));
		ScoreManager::updateHighScores();
		return;
	}




	// now to enable developers mode i will check for a specific key when it is pressed all 4 characters will get seperate 4
	// weapons and will become immortal
	if (Keyboard::isKeyPressed(Keyboard::I)) {

		// here i will check if developer mode is active
		if (PlayerSoldier::getDevMode()) {

			// here i will bring back to normal mode
			PlayerSoldier::setDevMode(false);


		}
		else {

			// this means that dev mode is not active so i will activate it and give seperate weapon to each player
			PlayerSoldier::setDevMode(true);

			allPlayers[0]->equipWeapon(new HeavyMachineGun(-1));
			allPlayers[1]->equipWeapon(new LaserGun(-1));
			allPlayers[2]->equipWeapon(new RocketLauncher(-1));
			allPlayers[3]->equipWeapon(new FlameShotGun(-1));

		}
	}









	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		if (!zPressed) {
			zPressed = true;
			// here i will switch the character
			float oldX = player->getPositionX();
			float oldY = player->getPositionY();
			float velX = player->getVelocityX();
			float velY = player->getVelocityY();

			currentCharacterIndex++;
			if (currentCharacterIndex > 3)
				currentCharacterIndex = 0;

			player = allPlayers[currentCharacterIndex];

			player->setPositionX(oldX);
			player->setPositionY(oldY);
			player->setVelocityX(velX);
			player->setVelocityY(velY);


			// also update targets for enemies
			for (int i = 0; i < entityMgr.getCount(); i++)
				entityMgr.getEntity(i)->setPlayer(player);
		}
	}


	else {
		zPressed = false;
	}

	// i am using E to enter a vehicle
	if (Keyboard::isKeyPressed(Keyboard::E)) {

		// i will loop through all the entities and check for the vehicles
		for (int i = 0; i < entityMgr.getCount(); i++) {

			Entity* e = entityMgr.getEntity(i);

			if (e->getHitbox().getType() == ColliderType::Vehicle) {

				Vehicle* v = (Vehicle*)e;

				// if it is a vehicle and is not occupied currently
				if (!v->getIsOccupied()) {

					// then i would check the distance to it
					float dx = player->getPositionX() - v->getPositionX();
					float dy = player->getPositionY() - v->getPositionY();
					float dist = sqrt(dx * dx + dy * dy);

					// if distance is less than my threshhold which is 100 so player gets on on it
					if (dist < 100.0f) {

						v->getOn(player);
						break; // break the loop to enter one vehicle only
					}
				}

			}

		}
	}

















	// in every frame i am going to check for water
	int playerTileX = (int)(player->getPositionX() + 60.0f) / CELL_SIZE;
	int playerTileY = (int)(player->getPositionY() + 120.0f) / CELL_SIZE;


	bool touchingWater = false;

	if (playerTileX >= 0 && playerTileX < LVL_WIDTH && playerTileY >= 0 && playerTileY < LVL_HEIGHT) {

		// if it is water
		if (lvl[playerTileY][playerTileX] == '~') {
			touchingWater = true;
		}
	}




	//audioMgr.updateWaterState(touchingWater);










	// update the player manually
	// i will check if player is alive
	if (player->getIsAlive()) {

		// if so update just and move on
		player->update(dt);
		checkTileCollision(player);
	}
	else {
		// if player is not alive i will check for respawning if he has lives left
		if (player->getLives() > 0) {
			player->setLives(player->getLives() - 1);
			player->resetStatus();

			// Respawn player
			player->setPositionX(levelMgr.getSpawnCol() * CELL_SIZE);
			player->setPositionY(levelMgr.getSpawnRow() * CELL_SIZE);
			player->setVelocityX(0);
			player->setVelocityY(0);
		}
		else {
			// if no lives are left games is over and move back to menu
			manager->changeState(new ModeSelectState(manager, window));
			ScoreManager::updateHighScores();
			return;
		}
	}





	if (currentLevel == 4) {


		/// first cleanup the current boss and move to next phase
		if (currentBoss != nullptr && currentBoss->getHasRetreated()) {
			currentBoss = nullptr;
			bossPhase++;


			// now for phase 4
			if (bossPhase == 4) {

				entityMgr.clear();

				levelMgr.generateDesign(lvl, "assets/Levels/Boss-Phase 4.txt", player, &entityMgr, &projMgr);

				// respawn the player at new level
				player->setPositionX(levelMgr.getSpawnCol() * CELL_SIZE);
				player->setPositionY(levelMgr.getSpawnRow() * CELL_SIZE);

				// set level in projectile manager too
				projMgr.setLevel(lvl, LVL_HEIGHT, LVL_WIDTH, CELL_SIZE, &entityMgr);
			}

		}

		// Now here i will first check for the phase 1 and spawn the boss of phase 1 at fixed coordinates
		if (bossPhase == 1 && currentBoss == nullptr) {
			currentBoss = new IronNokana(40 * CELL_SIZE, 20 * CELL_SIZE, player, &entityMgr, &projMgr);
			entityMgr.add(currentBoss);

		}

		// I have made sure that the aerial boss spawns only when player has entered the aerial coordinate
		if (bossPhase == 2 && currentBoss == nullptr && player->getPositionX() > 80 * CELL_SIZE) {
			currentBoss = new HairbusterRiberts(108 * CELL_SIZE, 9 * CELL_SIZE, player, &entityMgr, &projMgr);
			entityMgr.add(currentBoss);

		}

		// Similarly for aquatic boss
		if (bossPhase == 3 && currentBoss == nullptr && player->getPositionX() > 128 * CELL_SIZE) {

			// put a slug mariner there for the player to use
			SlugMariner* mariner = new SlugMariner(153 * CELL_SIZE, 22 * CELL_SIZE);
			entityMgr.add(mariner);

			currentBoss = new SeaSatan(160 * CELL_SIZE, 23 * CELL_SIZE, player, &entityMgr, &projMgr);
			entityMgr.add(currentBoss);

		}

		if (bossPhase == 4 && currentBoss == nullptr) {

			// spawn the boss
			currentBoss = new UltimateBoss(player->getPositionX() + 800.0f, 25 * CELL_SIZE, player, &entityMgr, &projMgr);
			entityMgr.add(currentBoss);
		}

	}














	// would later update all entities and levels and camera and record Frames as well
	entityMgr.updateAll(dt);


	for (int i = 0; i < entityMgr.getCount(); i++) {

		// get the current entity
		Entity * e = entityMgr.getEntity(i);

		// then i will check if it is a fire pool
		if (e->getHitbox().getType() == ColliderType::FirePool) {
			
			// cast it to fire pool
			FirePool* fp = (FirePool*)e;

			// Apply damage to player of fire pool
			fp->applyDamageTo(player);

			for (int j = 0; j < entityMgr.getCount(); j++) {


				Entity* target = entityMgr.getEntity(j);


				// if it is not itself apply the damage
				if (e != target) {
					fp->applyDamageTo(target);

				}

			}

		}
		
	}








	for (int i = 0; i < entityMgr.getCount(); i++) {
		checkTileCollision(entityMgr.getEntity(i));
	}





	entityMgr.removeDead();

	projectileManager.update(dt);
	projectileManager.checkTileCollision();
	projectileManager.checkEntityCollision(entityMgr);
	projectileManager.removeDeadProjectiles();





	// now also to update the collectibles
	for (int i = 0; i < entityMgr.getCount(); i++) {

		Entity* e = entityMgr.getEntity(i);

		// Check if it is a collectible
		if (e->getHitbox().getType() == ColliderType::Collectibles) {

			// now using my collider i will check if they collide
			if (player->getHitbox().checkCollision(e->getHitbox())) {
				Collectibles* item = (Collectibles*)e;

				// If this needs input to interact such as supply crate and POW prisoner use E to interact
				if (item->needsInput()) {

					if (Keyboard::isKeyPressed(Keyboard::E)) { 
						item->interact(player);
					}

				}
				else {
					// if its food interact instantly
					item->interact(player);

				}

			}

		}

	}


	camera.follow(player->getPositionX(), player->getPositionY());
	
	// in survival state we have access to the window so here i will find the mouse positions and pass it down to the player so that we can use it
	// in its states
	// this gives us the pixel coordinates of the mouse according to our window
	Vector2i pixelPositions = Mouse::getPosition(*window);
	// now to make them according to out world i add the camera offsets to both x and y coordinates
	Vector2f worldPositions;
	worldPositions.x = pixelPositions.x + camera.getOffsetX();
	worldPositions.y = pixelPositions.y + camera.getOffsetY();

	// now pass this over to player to handle it in current state
	player->handleMouse(worldPositions);



	

	if (levelComplete()) {
		
		if (ScoreManager::hasFlawlessVictory)
			ScoreManager::addScore(5000);

		ScoreManager::resetVictory();

		if (currentLevel < 4) {
			ScoreManager::addScore(1000);
		}

		currentLevel++;

		if (currentLevel > 4) {
			manager->changeState(new ModeSelectState(manager, window));
			ScoreManager::updateHighScores();
		}
		
		else {
			
			loadLevel(currentLevel);
		}

		return;

	}



	// also update all the projectiles
	projMgr.update(dt);
	projMgr.checkTileCollision();
	projMgr.checkEntityCollision(entityMgr);

	// Manually check player
	for (int i = 0; i < projMgr.getMaxProjectiles(); i++) {
		Projectile* p = projMgr.getProjectile(i);
		if (p == nullptr || !p->isActive()) { continue; }

		if (!p->getIsPlayerOwned()) { // If it's an enemy bullet
			if (p->getHitbox().checkCollision(player->getHitbox())) {
				player->takeDamage(1);
				p->deactivate();

			}

		}

	}

	projMgr.removeDeadProjectiles();

}

bool SurvivalState::levelComplete() {

	if (currentLevel < 4) {
		int count = 0;

		for (int i = 0; i < entityMgr.getCount(); i++) {

			// check for enemies
			if (entityMgr.getEntity(i)->getHitbox().getType() == ColliderType::Enemy) {
				count++;
			}
		}

		// is any enemy gets stuck end by going out of level
		bool reachedEnd = (player->getPositionX() > 190 * CELL_SIZE);


		if (count == 0 || reachedEnd)
			return true;
		
		return false;
	}
	else {

		if (bossPhase > 4)
			return true;
		else
			return false;

	}

	return false;
}

void SurvivalState::draw(sf::RenderWindow& window) {
	if (currentLevel == 4) {
		bossSprite.setPosition(0, 0);
		window.draw(bossSprite);
	} else {
		bgSprite.setPosition(0, 0);
		window.draw(bgSprite);
	}
	
	// here i will also render the red hue part
	int currState = player->getDamageState();

	// if player is in vehicle get the damage state of vehicle
	if (!player->getVisible()) {

		// find the ocuppied vehicle
		for (int i = 0; i < entityMgr.getCount(); i++) {

			Entity* e = entityMgr.getEntity(i);

			if (e->getHitbox().getType() == ColliderType::Vehicle) {

				// i will change this pointer to vehicle pointer
				Vehicle* v = (Vehicle*)e;

				if (v->getIsOccupied()) {
					currState = v->getDamageState();
					break;
				}
			}
		}
	}







	
	if (lvl == NULL) { std::cout << "lvl is NULL" << std::endl; return; }
	//visible cell range on camera
	int startCol = (int)(camera.getOffsetX() / CELL_SIZE);
	int endCol = (int)((camera.getOffsetX() + 1600) / CELL_SIZE) + 1;
	int startRow = (int)(camera.getOffsetY() / CELL_SIZE);
	int endRow = (int)((camera.getOffsetY()+900) / CELL_SIZE) + 1;

	if (startCol < 0) {
		startCol = 0;
	}
	if (startRow < 0) {
		startRow = 0;
	}
	if (endCol > LVL_WIDTH) {
		endCol = LVL_WIDTH;
	}
	if (endRow > LVL_HEIGHT) {
		endRow = LVL_HEIGHT;
	}

	for (int i = startRow; i < endRow; i++) {
		for (int j = startCol; j < endCol; j++) {

			if (lvl == NULL) { std::cout << "LVL is NULL" << endl; return; }
			char c = lvl[i][j];
			sf::Sprite* s = NULL;

			if (c == 'g') { s = &wallSprite; }
			else if (c == 's') {
				s = &stoneSprite;
			}
			else if (c == '~') {
				s = &waterSprite;
			}
			else if (c == '#') {
				s = &bedrockSprite;
			}
			if (s != NULL) 
			{
				
				s->setPosition(j * CELL_SIZE - camera.getOffsetX(), i * CELL_SIZE - camera.getOffsetY());
				window.draw(*s);
			}
		}
	}


	// need to add entity draw and ui draw later
	entityMgr.draw(window, camera);
	if (player->getIsAlive() && player->getVisible()) {
		player->render(window, camera);
	}
	projectileManager.render(window, camera);

	projMgr.render(window, camera);




	// now i will use damage state of player or vehicle if he is in vehicle

	if (currState > 0) {

		// here i will once render this red hue image
		redHueSprite.setPosition(0, 0);

		window.draw(redHueSprite);

		// if the state is greater than one again draw to show intensity
		if (currState > 1)
			window.draw(redHueSprite);
	}




	hud.render(window, player);

	
}











void SurvivalState::checkTileCollision(Entity* p) {

	if (!p || !lvl) return;

	// reset ground flag each frame; collision detection will re-set it if on solid ground
	p->setOnGround(false);

	float pw = (p->getHitbox().getWidth() > 120.0f) ? p->getHitbox().getWidth() : 120.0f;
	float ph = (p->getHitbox().getHeight() > 128.0f) ? p->getHitbox().getHeight() : 128.0f;

	// World Bounds Checking
	if (p->getPositionX() < 0) {

		p->setPositionX(0);
		p->setVelocityX(0);

	}

	else if (p->getPositionX() + pw > LVL_WIDTH * CELL_SIZE) {

		p->setPositionX((float)(LVL_WIDTH * CELL_SIZE) - pw);
		p->setVelocityX(0);

	}

	if (p->getPositionY() < 0) {

		p->setPositionY(0);
		p->setVelocityY(0);

	}

	else if (p->getPositionY() + ph > LVL_HEIGHT * CELL_SIZE) {

		p->setPositionY((float)(LVL_HEIGHT * CELL_SIZE) - ph);
		p->setVelocityY(0);

		p->setOnGround(true);


	}

	// two passes: vertical first, then horizontal — gives stable platformer feel
	for (int pass = 0; pass < 2; pass++) {
		float px = p->getPositionX();
		float py = p->getPositionY();

		int cStart = (int)(px / CELL_SIZE);

		int cEnd = (int)((px + pw - 1) / CELL_SIZE);

		int rStart = (int)(py / CELL_SIZE);

		int rEnd = (int)((py + ph - 1) / CELL_SIZE);


		if (cStart < 0) cStart = 0;

		if (cEnd >= LVL_WIDTH) cEnd = LVL_WIDTH - 1;

		if (rStart < 0) rStart = 0;

		if (rEnd >= LVL_HEIGHT) rEnd = LVL_HEIGHT - 1;


		for (int r = rStart; r <= rEnd; r++) {

			for (int c = cStart; c <= cEnd; c++) {



				char tile = lvl[r][c];

				if (tile == ' ' || tile == '~') continue;

				float tx = (float)(c * CELL_SIZE);

				float ty = (float)(r * CELL_SIZE);

				float overlapLeft = (px + pw) - tx;

				float overlapRight = (tx + CELL_SIZE) - px;

				float overlapTop = (py + ph) - ty;

				float overlapBottom = (ty + CELL_SIZE) - py;

				if (overlapLeft <= 0 || overlapRight <= 0 || overlapTop <= 0 || overlapBottom <= 0)
					continue;

				float minX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
				float minY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

				if (pass == 0) {
					// vertical pass
					if (minY <= minX) {
						if (overlapTop < overlapBottom) {

							// feet hit top of tile — landed on ground
							p->setPositionY(ty - ph);
							p->setVelocityY(0.0f);
							p->setOnGround(true);

						}

						else {
							// head hit underside of tile
							p->setPositionY(ty + CELL_SIZE);
							p->setVelocityY(0.0f);

						}
					}

				}

				else {
					// horizontal pass
					if (minX < minY) {
						if (overlapLeft < overlapRight)
							p->setPositionX(tx - pw);
						else
							p->setPositionX(tx + CELL_SIZE);
					}
				}
			}
		}
	}
}

SurvivalState::~SurvivalState() {
	freeLevel();

	for (int i = 0; i < 4; i++)
		delete allPlayers[i];

}
