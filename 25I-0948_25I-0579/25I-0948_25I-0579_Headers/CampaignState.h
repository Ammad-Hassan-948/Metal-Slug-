#pragma once
#include "GameState.h"
#include "Camera.h"
#include "EntityManager.h"
#include "ProjectileManager.h"
#include "GameConstants.h"
#include <SFML/Graphics.hpp>

class GameStateManager;
class PlayerSoldier;
class CampaignWorld;
class Entity;


class GameStateManager;

class CampaignState :public GameState {
	static const int PHASE_SELECT  = 0;
	static const int PHASE_PLAY    = 1;
	static const int PHASE_WIN     = 2;
	static const int PHASE_GAMEOVER= 3;

	GameStateManager* manager;
	sf::RenderWindow* window;
    EntityManager    entityMgr;
    ProjectileManager projectileManager;

    int phase;
    int selectedProfile;   // 0 for ormal 1 for amplified 2 for flat
    float keyDelay;          // debounce for arrow/enter keys


    float endTimer;

    sf::Font font;
    sf::Text titleText;
    sf::Text profileTexts[3];
    sf::Text hudText;
    sf::Text endText;
    sf::Texture blockTextures[BlockType::COUNT];
    sf::Sprite  blockSprite;

    CampaignWorld* world;

    Camera campaignCam;

    PlayerSoldier* allPlayers[4];
    PlayerSoldier* player;
    int  currentCharIndex;
    bool zPressed;
    bool
        lastMartianWasAir;
    //checkTileCollision is not called in this state 
    //  only entity collision is checked.
    static const int DL_SIZE = 2;
    char  dummyData[DL_SIZE][DL_SIZE];//for projectile initialization
    char* dummyPtrs[DL_SIZE];


    void loadBlockTextures(); void createWorld(int profileKind); void spawnPlayers();
    void cleanupPlayers(); void handleSpawnRequest(); void countAndReportDeaths();
    void checkCampaignTileCollision(Entity* e); void updateCamera();
    void drawTerrain(sf::RenderWindow& win); void drawHUD(sf::RenderWindow& win);
    void updateProfileSelect(float dt); void drawProfilesSelect(sf::RenderWindow& win);

public:
	CampaignState(GameStateManager* mgr, sf::RenderWindow* win);
	~CampaignState() override;
	void update(float dt);
	void draw(sf::RenderWindow& win);
};