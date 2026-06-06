#pragma once
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>

GameStateManager::~GameStateManager() {
	delete activeState;
}

void GameStateManager::changeState(GameState* NewGameState) {
	delete activeState;
	activeState = NewGameState;
}
//void GameStateManager::handleEvent(sf::Event& ev) {
//	if (activeState) {
//		activeState->handleEvent(ev);
//	}
//}

void GameStateManager::update(float dt) {
	if (activeState) {
		activeState->update(dt);
	}
}

void GameStateManager::draw(sf::RenderWindow& window) {
	if (activeState) {
		activeState->draw(window);
	}
	
}

