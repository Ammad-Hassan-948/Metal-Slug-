#pragma once
#include "GameState.h"
#include "EntityManager.h"
#include "Camera.h"
#include "LevelManager.h"
#include"ProjectileManager.h"
#include "AudioManager.h"
#include"HUD.h"

class EntityManager;
class Camera;
class TimeLineRecorder;
class ScoreTracker;

class GameStateManager;

class Vehicle;

class PlayerSoldier;
class MetalSlug;


class Boss;

class SurvivalState:public GameState {

	// for audio reading
	AudioManager audioMgr;
	HUD hud;

	int currentLevel; //1, 2, 3, 4(boss)
	char** lvl;

	GameStateManager* manager;
	sf::RenderWindow* window;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Texture bossTexture;
	sf::Sprite bossSprite;
	sf::Texture wallTexture;
	sf::Texture stoneTexture;
	sf::Texture waterTexture;
	sf::Texture bedrockTexture;

	
		//stone, water bedrock
	sf::Sprite wallSprite;
	sf::Sprite stoneSprite;
	sf::Sprite waterSprite;
	sf::Sprite bedrockSprite;



	EntityManager entityMgr;
	ProjectileManager projectileManager;
	LevelManager levelMgr;
	ProjectileManager projMgr;
	//LevelManager levelMgr;//to be added later
	Camera camera;

	PlayerSoldier* allPlayers[4];
	PlayerSoldier* player;
	int currentCharacterIndex;
	bool zPressed;

	sf::Texture redHueTexture;
	sf::Sprite redHueSprite;

	//belong to the class not any object
	static const int CELL_SIZE = 64;
	static const int LVL_HEIGHT = 55;
	static const int LVL_WIDTH = 460;



	void allocateLevel();
	void freeLevel();
	void loadLevel(int levelNum);
	bool levelComplete();
	void checkTileCollision(Entity* p);


	int bossPhase;
	Boss* currentBoss;


public:
	SurvivalState(GameStateManager* manager, sf::RenderWindow* window, int startLevel);
	ProjectileManager* getProjectileManager();
	void update(float dt);
	void draw(sf::RenderWindow& window);
	~SurvivalState();

};
