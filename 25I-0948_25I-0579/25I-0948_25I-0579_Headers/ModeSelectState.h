#pragma once
#include "GameState.h"

class GameStateManager;

class ModeSelectState :public GameState {
	GameStateManager* manager;
	sf::RenderWindow* window;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Font font;
	sf::Text title;
	sf::Text option1, option2, option3;//survival, campaign, self-play
	int selectedIndex;//0, 1 or 2
	float keyDelay;//for debouncing arrow keys

public:
	ModeSelectState(GameStateManager* mgr, sf::RenderWindow* win);
	void update(float dt);
	void draw(sf::RenderWindow& win);
};
