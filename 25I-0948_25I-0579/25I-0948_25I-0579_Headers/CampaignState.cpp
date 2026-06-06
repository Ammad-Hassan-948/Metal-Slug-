#include "CampaignState.h"
#include "CampaignWorld.h"
#include "GameStateManager.h"
#include "ModeSelectState.h"
#include "SurvivalState.h"
#include "MarcoRossi.h"
#include "EriKasamoto.h"
#include "FiolinaGermi.h"
#include "Tarma.h"
#include "RebelSoldier.h"
#include "BazookaSoldier.h"
#include "GrenadeSoldier.h"
#include "MummyWarrior.h"
#include "ShieldedSoldier.h"
#include "Zombie.h"
#include "MartianAir.h"
#include "MartianGround.h"
#include "FlyingTara.h"
#include "EnemySub.h"
#include "M15ABradley.h"
#include "Enemy.h"
#include "Pistol.h"

#include <cmath>  

using namespace sf;


static const float SCREEN_W = 1600.0f;
static const float SCREEN_H = 900.0f;

static const float SPAWN_BLOCK_X = 5000.0f;

static const float CAM_WORLD_W = 100000.0f * (float)CampaignConstants::BLOCK_SIZE_PIXELS;;

static const float CAM_WORLD_H = (float)(CampaignConstants::WORLD_HEIGHT * CampaignConstants::BLOCK_SIZE_PIXELS);

CampaignState::CampaignState(GameStateManager* mgr, sf::RenderWindow* win) :
	manager(mgr),
	window(win),
	phase(PHASE_SELECT),
	selectedProfile(0),
	keyDelay(0.3f), world(nullptr), campaignCam(SCREEN_W, SCREEN_H, CAM_WORLD_W
		, CAM_WORLD_H),
	player(nullptr), currentCharIndex(0),
	zPressed(false), lastMartianWasAir(false), endTimer(0.0f)

{
	for (int i = 0; i < 4; i++) {
		allPlayers[i] = nullptr;
	}


	for (int i = 0; i < DL_SIZE; i++) {
		dummyPtrs[i] = dummyData[i];

		for (int j = 0; j < DL_SIZE; j++) {

			dummyData[i][j] = ' ';
		}
	}


	font.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_misc/font.ttf");
	titleText.setFont(font); titleText.setString("Select TERRAIN Profile");
	titleText.setCharacterSize(55); titleText.setFillColor(Color::White);
	titleText.setPosition(450, 180);

	const char* labels[3] = { "NORMAL biomes",

										"Amplified Extreme peaks and deep oceam",

						"FLAT mostly plain and gentle terrain" };

	for (int i = 0; i < 3; i++) {

		profileTexts[i].setFont(font); profileTexts[i].setString(labels[i]);
		profileTexts[i].setCharacterSize(36); profileTexts[i].setPosition(380, 340.0f + i * 90.0f);
	}

	hudText.setFont(font); hudText.setCharacterSize(24);
	hudText.setFillColor(Color::White); hudText.setPosition(20, 20);

	endText.setFont(font); endText.setCharacterSize(72);
	endText.setPosition(400, 360);

	loadBlockTextures();
}

CampaignState::~CampaignState()
{
	delete world; world = nullptr;
	cleanupPlayers();
}

void CampaignState::update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		manager->changeState(new ModeSelectState(manager, window));
		return;
	}

	if (phase == PHASE_SELECT) {
		updateProfileSelect(dt);
		return;
	}

	if (phase == PHASE_WIN || phase == PHASE_GAMEOVER) {
		endTimer -= dt;
		if (endTimer <= 0.0f) {
			manager->changeState(new ModeSelectState(manager, window));
		}
		return;
	}

	if (!player->getIsAlive()) {
		bool found = false;
		for (int i = 1; i <= 4; i++) {
			int next = (currentCharIndex + i) % 4;
			if (allPlayers[next] && allPlayers[next]->getIsAlive()) {
				currentCharIndex = next;
				player = allPlayers[currentCharIndex];
				for (int j = 0; j < entityMgr.getCount(); j++)
					entityMgr.getEntity(j)->setPlayer(player);
				found = true;
				break;
			}
		}
		if (!found) {
			phase = PHASE_GAMEOVER;
			endTimer = 3.0f;
			endText.setFillColor(sf::Color::Red);
			endText.setString("GAME OVER");
			return;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (!zPressed) {
			zPressed = true;
			float oldX = player->getPositionX();
			float oldY = player->getPositionY();
			float velX = player->getVelocityX();
			float velY = player->getVelocityY();
			currentCharIndex = (currentCharIndex + 1) % 4;
			player = allPlayers[currentCharIndex];
			player->setPositionX(oldX);
			player->setPositionY(oldY);
			player->setVelocityX(velX);
			player->setVelocityY(velY);
			for (int i = 0; i < entityMgr.getCount(); i++)
				entityMgr.getEntity(i)->setPlayer(player);
		}
	}



	else {
		zPressed = false;
	}

	world->update(dt, player->getPositionX());

	if (player->getIsAlive()) {
		player->update(dt);
		checkCampaignTileCollision(player);
	}

	entityMgr.updateAll(dt);
	for (int i = 0; i < entityMgr.getCount(); i++)
		checkCampaignTileCollision(entityMgr.getEntity(i));

	handleSpawnRequest();
	countAndReportDeaths();

	if (world->isObjectiveComplete()) {
		phase = PHASE_WIN;
		endTimer = 4.0f;
		endText.setFillColor(sf::Color::Green);
		endText.setString("YOU WIN!");
		return;
	}

	entityMgr.removeDead();

	projectileManager.update(dt);

	if (world) {
		const int BS = CampaignConstants::BLOCK_SIZE_PIXELS;
		const int WH = CampaignConstants::WORLD_HEIGHT;
		for (int i = 0; i < projectileManager.getMaxProjectiles(); i++) {
			Projectile* p = projectileManager.getProjectile(i);
			if (!p || !p->isActive()) continue;
			float px = p->getHitbox().getX();
			float py = p->getHitbox().getY();
			float pw = p->getHitbox().getWidth();
			float ph = p->getHitbox().getHeight();
			int c0 = (int)(px / BS);
			int c1 = (int)((px + pw) / BS);
			int r0 = (int)(py / BS);
			int r1 = (int)((py + ph) / BS);
			if (r0 < 0) r0 = 0;
			if (r1 >= WH) r1 = WH - 1;
			bool hit = false;
			for (int r = r0; r <= r1 && !hit; r++) {
				for (int c = c0; c <= c1 && !hit; c++) {
					int worldY = WH - 1 - r;
					if (world->isSolid(c, worldY)) {
						p->onHit(nullptr);
						hit = true;
					}
				}
			}
		}
	}

	projectileManager.checkEntityCollision(entityMgr);

	if (player && player->getIsAlive()) {
		for (int i = 0; i < projectileManager.getMaxProjectiles(); i++) {
			Projectile* p = projectileManager.getProjectile(i);
			if (p == nullptr || !p->isActive()) { continue; }
			if (!p->getIsPlayerOwned()) {
				if (p->getHitbox().checkCollision(player->getHitbox())) {
					player->takeDamage(1);
					p->deactivate();
				}
			}
		}
	}

	projectileManager.removeDeadProjectiles();

	updateCamera();
}

void CampaignState::draw(sf::RenderWindow& window) {

	if (phase == PHASE_SELECT) {
		drawProfilesSelect(window);
		return;
	}

	if (phase == PHASE_WIN || phase == PHASE_GAMEOVER) {
		window.draw(endText);
		return;
	}

	drawTerrain(window);
	entityMgr.draw(window, campaignCam);
	if (player && player->getIsAlive() && player->getVisible()) {

		player->render(window, campaignCam);
	}

	projectileManager.render(window, campaignCam);
	drawHUD(window);
}

void CampaignState::loadBlockTextures()
{
	blockTextures[BlockType::BEDROCK].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/deepslate_top.png");

	blockTextures[BlockType::STONE].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/stone.png");

	blockTextures[BlockType::DIRT].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/dirt.png");

	blockTextures[BlockType::GRASS].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/grass_block_side.png");

	blockTextures[BlockType::SAND].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/andesite.png");

	blockTextures[BlockType::WATER].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/water.jpeg");

	if (!blockTextures[BlockType::SNOW].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/snow.png")) {

		//adding stone as a placeholder for snow
		blockTextures[BlockType::SNOW].loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_Assets/stone.png");

	}
}

void CampaignState::createWorld(int profileKind)
{

	delete world;

	world = new CampaignWorld(profileKind, 12345u); //seed can be changed by me to vary terrain


	projectileManager.setLevel(nullptr, 100000, 100000,
		CampaignConstants::BLOCK_SIZE_PIXELS, &entityMgr);//fake large bounds for pojectiles so that dummy data is not accessed

	//player spawing
	float spawnPixelX = SPAWN_BLOCK_X * (float)CampaignConstants::BLOCK_SIZE_PIXELS;

	world->update(0.0f, spawnPixelX);


	spawnPlayers();
}

void CampaignState::spawnPlayers()
{

	cleanupPlayers();


	const int BlockSize = CampaignConstants::BLOCK_SIZE_PIXELS;

	const int worldHeight = CampaignConstants::WORLD_HEIGHT;


	int blockX = (int)SPAWN_BLOCK_X;

	float spawnPixelX = SPAWN_BLOCK_X * (float)BlockSize;

	int surfaceY_bottom = world->getSurfaceY(blockX);//asking the world for surface height at spawn col


	int screenRow = worldHeight - surfaceY_bottom;

	float spawnPixelY = (float)(screenRow - 2) * (float)BlockSize;

	allPlayers[0] = new MarcoRossi(spawnPixelX, spawnPixelY);
	allPlayers[1] = new EriKasamoto(spawnPixelX, spawnPixelY);
	allPlayers[2] = new FiolinaGermi(spawnPixelX, spawnPixelY);
	allPlayers[3] = new Tarma(spawnPixelX, spawnPixelY);

	for (int i = 0; i < 4; i++) {
		allPlayers[i]->setPistol(new Pistol(-1));
		allPlayers[i]->setProjectileManager(&projectileManager);
	}

	currentCharIndex = 0;
	player = allPlayers[0];

}

void CampaignState::cleanupPlayers()
{
	for (int i = 0; i < 4; i++) {
		delete allPlayers[i];
		allPlayers[i] = nullptr;
	}

	player = nullptr;
}

void CampaignState::handleSpawnRequest()
{

	if (!world || !world->hasSpawnRequest()) {
		return;
	}

	float spawnX, spawnY;

	int eType;

	world->consumeSpawnRequest(spawnX, spawnY, eType);

	Enemy* e = nullptr;

	if (eType == EnemyType::REBEL_SOLDIER) {
		e = new RebelSoldier(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::BAZOOKA_SOLDIER) {
		e = new BazookaSoldier(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::GRENADE_SOLDIER) {
		e = new GrenadeSoldier(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::MUMMY) {
		e = new MummyWarrior(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::SHIELDED_SOLDIER) {
		e = new ShieldedSoldier(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::ZOMBIE) {
		e = new Zombie(spawnX, spawnY, player);
	}


	else if (eType == EnemyType::MARTIAN) {

		lastMartianWasAir = !lastMartianWasAir;

		if (lastMartianWasAir) {
			e = new MartianAir(spawnX, spawnY, player);
		}
		else {
			e = new MartianGround(spawnX, spawnY, player);
		}

	}

	else if (eType == EnemyType::FLYING_TARA) {
		e = new FlyingTara(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::ENEMY_SUB) {
		e = new EnemySub(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::M15A_BRADLEY) {
		e = new M15ABradley(spawnX, spawnY, player);
	}

	else if (eType == EnemyType::PARATROOPER) {
		static int paraCounter = 0;
		int choice = paraCounter % 4;
		paraCounter++;
		if (choice == 0)      e = new RebelSoldier(spawnX, spawnY, player);
		else if (choice == 1) e = new BazookaSoldier(spawnX, spawnY, player);
		else if (choice == 2) e = new GrenadeSoldier(spawnX, spawnY, player);
		else                  e = new ShieldedSoldier(spawnX, spawnY, player);
		if (e) e->setIsParatrooper(true);
	}

	if (e != nullptr) {
		e->setProjectileManager(&projectileManager);
		entityMgr.add(e);
	}


}

void CampaignState::countAndReportDeaths()
{

	if (!world) { return; }

	for (int i = 0; i < entityMgr.getCount(); i++) {

		Entity* e = entityMgr.getEntity(i);

		if (e->getIsAlive()) { continue; }

		if (e->getHitbox().getType() != ColliderType::Enemy) { continue; }

		Enemy* enemy = (Enemy*)e;
		int type = enemy->getIsParatrooper() ? EnemyType::PARATROOPER : enemy->getEnemyTypeId();

		if (type >= 0) {
			world->onEnemyKilled(type);
		}


	}
}

void CampaignState::checkCampaignTileCollision(Entity* e)
{

	if (!e || !world) { return; }



	e->setOnGround(false);

	const int  BS = CampaignConstants::BLOCK_SIZE_PIXELS;
	const int  WH = CampaignConstants::WORLD_HEIGHT;

	float PW = e->getHitbox().getWidth();
	float PH = e->getHitbox().getHeight();
	if (PW < 120.0f) PW = 120.0f;
	if (PH < 128.0f) PH = 128.0f;

	float worldHeightPx = (float)(WH * BS);


	if (e->getPositionY() < 0.0f) {

		e->setPositionY(0.0f);

		e->setVelocityY(0.0f);
	}

	if (e->getPositionY() + PH > worldHeightPx) {

		e->setPositionY(worldHeightPx - PH);

		e->setVelocityY(0.0f);

		e->setOnGround(true);
	}

	for (int pass = 0; pass < 2; pass++) {

		float playerX = e->getPositionX();

		float playerY = e->getPositionY();

		int colStart = (int)floor(playerX / (float)BS);

		int colEnd = (int)floor((playerX + PW - 1.0f) / (float)BS);

		int rowStart = (int)(playerY / (float)BS);

		int rowEnd = (int)((playerY + PH - 1.0f) / (float)BS);

		if (rowStart < 0) {
			rowStart = 0;
		}

		if (rowEnd >= WH) {
			rowEnd = WH - 1;
		}

		for (int r = rowStart; r <= rowEnd; r++) {

			for (int c = colStart; c <= colEnd; c++) {


				int worldY = WH - 1 - r;

				if (!world->isSolid(c, worldY)) { continue; }


				float tileX = (float)(c * BS);

				float ty = (float)(r * BS);

				float overlapLeft = (playerX + PW) - tileX;

				float overlapRight = (tileX + BS) - playerX;

				float overlapTop = (playerY + PH) - ty;

				float overlapBottom = (ty + BS) - playerY;

				if (overlapLeft <= 0 || overlapRight <= 0 || overlapTop <= 0 || overlapBottom <= 0) {
					continue;
				}

				float minX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;

				float minY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

				if (pass == 0) {

					if (minY <= minX) {

						if (overlapTop < overlapBottom) {

							e->setPositionY(ty - PH);
							e->setVelocityY(0.0f);

							e->setOnGround(true);

						}

						else {

							e->setPositionY(ty + (float)BS);
							e->setVelocityY(0.0f);

						}
					}
				}

				else {

					if (minX < minY) {

						if (overlapLeft < overlapRight) {

							e->setPositionX(tileX - PW);
						}

						else {

							e->setPositionX(tileX + (float)BS);
						}
					}
				}
			}
		}
	}
}

void CampaignState::updateCamera()
{
	if (!player) { return; }
	campaignCam.follow(player->getPositionX(), player->getPositionY());
}

void CampaignState::drawTerrain(sf::RenderWindow& win)
{

	//iterating visible blocks, setting texture and drawing

	if (!world) { return; }

	const int blockSize = CampaignConstants::BLOCK_SIZE_PIXELS;
	const int worldHeight = CampaignConstants::WORLD_HEIGHT;

	float offX = campaignCam.getOffsetX(); float offY = campaignCam.getOffsetY();

	int startCol = (int)floor(offX / (float)blockSize) - 1;

	int endCol = (int)floor((offX + SCREEN_W) / (float)blockSize) + 1;


	int startRow = (int)(offY / (float)blockSize) - 1;
	int endRow = (int)((offY + SCREEN_H) / (float)blockSize) + 1;


	if (startRow < 0)  startRow = 0;
	if (endRow >= worldHeight) {
		endRow = worldHeight - 1;
	}


	for (int col = startCol; col <= endCol; col++) {

		for (int row = startRow; row <= endRow; row++) {

			int worldY = worldHeight - 1 - row;

			int blockType = world->getBlockType(col, worldY);

			if (blockType == BlockType::AIR) {

				continue;
			}



			float screenX = (float)(col * blockSize) - offX;

			float screenY = (float)(row * blockSize) - offY;


			blockSprite.setTexture(blockTextures[blockType]);

			blockSprite.setPosition(screenX, screenY);

			win.draw(blockSprite);


		}

	}
}

void CampaignState::drawHUD(sf::RenderWindow& win)
{

	if (!world) {
		return;
	}


	sf::String s = "CAMPAIGN | ESC:quit | Z:switch char";
	if (world->isRaining()) s += " | RAIN";

	hudText.setString(s); hudText.setPosition(10, 10);
	win.draw(hudText);
}

void CampaignState::updateProfileSelect(float dt)
{

	keyDelay -= dt;

	if (keyDelay > 0.0f)return;

	if (Keyboard::isKeyPressed(Keyboard::Down)) {

		selectedProfile = (selectedProfile + 1) % 3;

		keyDelay = 0.2f;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Up)) {

		selectedProfile = (selectedProfile + 2) % 3; keyDelay = 0.2f;
	}


	if (Keyboard::isKeyPressed(Keyboard::Enter)) {

		createWorld(selectedProfile); phase = PHASE_PLAY;
		keyDelay = 0.5f;
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {

		manager->changeState(new ModeSelectState(manager, window));

	}
}



void CampaignState::drawProfilesSelect(sf::RenderWindow& win)
//profile selection screen rendering
{

	win.draw(titleText);

	for (int i = 0; i < 3; i++) {

		profileTexts[i].setFillColor(i == selectedProfile ? Color::Yellow : Color::White);

		win.draw(profileTexts[i]);
	}
}