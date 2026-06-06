#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class GameStateManager {
private:
	GameState* activeState;

public:
	GameStateManager():activeState(nullptr){}
	~GameStateManager();
	void changeState(GameState* NewGameState);
	//void handleEvent(sf::Event& ev);
	void update(float dt);
	void draw(sf::RenderWindow& window);

};


