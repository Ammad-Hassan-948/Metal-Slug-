#pragma once
#include "GameState.h"

class GameStateManager;

class MenuState :public GameState {
	GameStateManager* manager; // for change state
	sf::RenderWindow* window;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Font font;
	sf::Text text;
	sf::Text leaderboardTitle;
	sf::Text leaderboardContent;

	void appendString(const char* toAppend, char* buffer, int& i);
	void appendInt(int num, char* buffer, int& i);

public:
	MenuState(GameStateManager* mgr, sf::RenderWindow* win);
	void update(float dt) override;
	void draw(sf::RenderWindow& win) override;

};
